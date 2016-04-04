# tic.OutputMGR

The OutputMGR writes files. It is used to make additional processing on the files easier, because most toolkits need an additional compilation step to complete the transformation from TiC to their individual dialect of TiBasic. 

## .set_file(file_path, content)

Sets the content of the given file. Files will be written once the toolkit has finished, or transformed as the toolkit specified. 

## .file(file_path) (str)

Returns the contents of a file set with `set_file(file_path, content)`.
