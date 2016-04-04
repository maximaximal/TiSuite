# tic.ErrorHandler

An ErrorHandler handles user-created [errors](Error). It can be reached from python using the global `error_handler` object and outputs errors through the error reporting stack explained in [Handling Errors](/python-api/Handling-Errors).

## .handle([tic.Error](Error))

Handles the given error in the error handler of the compiler system. This can also lead to changes in the editor GUI which imports the compiler or just to console outputs. The [Error](Error) object has to be created using its constructor first.
