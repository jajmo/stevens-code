-module(watcher).
-author("Jason Ajmo").
-export([run/0]).

% Main method. Run this from the command line
run() -> 
    {ok, [ N ]} = io:fread("Enter number of sensors: ", "~d"),
    if N =< 1 ->
        io:fwrite("setup: Range must be at least 2~n", []);
    true ->
        createWatchers(0, N - 1)
    end.

% Spawns watchers
createWatchers(Start, Stop) when Start rem 10 =:= 0 ->
    _ = spawn(fun() -> spawnWatchers(Start, Stop) end),
    createWatchers(Start + 1, Stop);
createWatchers(Start, Stop) when Start =< Stop -> createWatchers(Start + 1, Stop);
createWatchers(_, _) -> ok.

% Spawns sensors
spawnWatchers(StartID, Stop) ->
    StopID = min(StartID + 9, Stop),
    spawnSensors(StartID, StopID + 1, []).

% Run the sensor monitor
spawnSensors(StartID, StopID, Processes) when StartID =/= StopID ->
    {PID, _} = spawn_monitor(sensor, run, [StartID, self()]),
    spawnSensors(StartID + 1, StopID, Processes ++ [{StartID, PID}]);
spawnSensors(_, _, Processes) ->
    printList(Processes),
    listen(Processes).

% Wait for messages from the sensors
listen(Processes) ->
    receive
        {ID, Message} -> 
            io:fwrite("[+] Reading from sensor [~p]: ~p~n", [ID, Message]),
            listen(Processes);
        {'DOWN', _, _, PID, {ID, Reason}} ->
            io:fwrite("[-] Sensor [~p] crashed: ~p~n", [ID, Reason]),
            NewProc = lists:delete({ID, PID}, Processes),
            {NewPID, _} = spawn_monitor(sensor, run, [ID, self()]),
            io:fwrite("[*] Sensor [~p] restarted. New sensor list:~n", [ID]),
            NewProcList = NewProc ++ [{ID, NewPID}],
            printList(NewProcList),
            listen(NewProcList)
    end.

% Print a list
printList([A|B]) -> io:fwrite("~w~n", [A]), printList(B);
printList([]) -> ok.