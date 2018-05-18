-module(interp).
-export([scanAndParse/1,runFile/1,runStr/1]).
-include("types.hrl").

loop(InFile,Acc) ->
    case io:request(InFile,{get_until,prompt,lexer,token,[1]}) of
        {ok,Token,_EndLine} ->
            loop(InFile,Acc ++ [Token]);
        {error,token} ->
            exit(scanning_error);
        {eof,_} ->
            Acc
    end.

scanAndParse(FileName) ->
    {ok, InFile} = file:open(FileName, [read]),
    Acc = loop(InFile,[]),
    file:close(InFile),
    {Result, AST} = parser:parse(Acc),
    case Result of 
	ok -> AST;
	_ -> io:format("Parse error~n")
    end.


-spec runFile(string()) -> valType().
runFile(FileName) ->
    valueOf(scanAndParse(FileName),env:new()).

scanAndParseString(String) ->
    {_ResultL, TKs, _L} = lexer:string(String),
    parser:parse(TKs).

-spec runStr(string()) -> valType().
runStr(String) ->
    {Result, AST} = scanAndParseString(String),
    case Result  of 
    	ok -> valueOf(AST,env:new());
    	_ -> io:format("Parse error~n")
    end.




-spec numVal2Num(numValType()) -> integer().
numVal2Num({num, N}) ->
    N.

-spec boolVal2Bool(boolValType()) -> boolean().
boolVal2Bool({bool, B}) ->
    B.

-spec valueOf(expType(),envType()) -> valType().
valueOf(Exp,Env) ->
    case Exp of
        {letExp, {id, _, Var}, Val, Exp1} -> 
            NewEnv = env:add(Env, Var, valueOf(Val, Env)),
            valueOf(Exp1, NewEnv);
        {plusExp, First, Second} -> {num, numVal2Num(valueOf(First, Env)) + numVal2Num(valueOf(Second, Env))};
        {diffExp, First, Second} -> {num, numVal2Num(valueOf(First, Env)) - numVal2Num(valueOf(Second, Env))};
        {isZeroExp, Exp1} -> {bool, numVal2Num(valueOf(Exp1, Env)) =:= 0};
        {ifThenElseExp, If, Then, Else} -> 
            case boolVal2Bool(valueOf(If, Env)) of
                true -> valueOf(Then, Env);
                _ -> valueOf(Else, Env)
            end;
        {appExp, Id, Param} -> 
            Fun = valueOf(Id, Env),
            {proc, Var, Body, OldEnv} = Fun,
            NewEnv = env:add(OldEnv, Var, valueOf(Param, Env)),
            valueOf(Body, NewEnv);
        {procExp, {id, _, Param}, Body} -> {proc, Param, Body, Env};
        {numExp, {num, _, Val}} -> {num, Val};
        {idExp, Var} -> valueOf(Var, Env);
        {id, _, Sym} -> env:lookup(Env, Sym);
        _ -> erlang:display("Unkonwn expression")
    end.