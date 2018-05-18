-module(sensor).
-author("Jason Ajmo").
-export([run/2]).

% Run a sensor
run(ID, ParentPID) -> 
    timer:sleep(rand:uniform(10000)),
    Measurement = rand:uniform(11),
    case Measurement < 11 of
        true -> 
            ParentPID ! {ID, Measurement},
            run(ID, ParentPID);
        _ -> exit({ID, anomalous_reading})
    end.