#pragma once
/*
    This class shows a result of user's operation on the server's side.
    Failure - a called function has failed or throwed an exception
    Success - a called function has finished correctly
*/
enum class ServerResult : bool {Failure = false, Success = true};
