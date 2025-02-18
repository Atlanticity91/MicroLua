--- CUSTOM FUNCTIONS
function get_use_vs( )
	return _ACTION ~= nil and _ACTION:find( '^vs' )
end

--- OUTPUT DIRS
OutputDirs = { }

OutputDirs[ 'Solution' ] = '%{wks.location}Solution/'
OutputDirs[ 'Bin' ] = '%{wks.location}bin/'
OutputDirs[ 'BinInt' ] = '%{wks.location}bin-int/'

--- THIRDPARTY LIBRARIES
IncludeDirs = { }

IncludeDirs[ 'MicroLua' ] = '%{wks.location}MicroLua/'
IncludeDirs[ 'MicroLuaTest' ] = '%{wks.location}MicroTest/'
IncludeDirs[ 'Lua' ] = '%{wks.location}Thirdparty/'

--- EXTENSION LIBRARIES
ExtensionDirs = { }

ExtensionDirs[ 'Devenv' ] = ( os.getenv( 'VS_PATH' )..'Common7/IDE/devenv.exe' )
ExtensionDirs[ 'MicroLuaDebugger' ] = '%{wks.location}MicroExtensions/VisualStudio/'
