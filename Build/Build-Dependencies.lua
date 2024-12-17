--- OUTPUT DIRS
OutputDirs = { }

OutputDirs[ "Solution" ] = "%{wks.location}/Solution/"
OutputDirs[ "Bin" ] = "%{wks.location}/bin/"
OutputDirs[ "BinInt" ] = "%{wks.location}/bin-int/"

--- THIRDPARTY LIBRARIES
IncludeDirs = { }

IncludeDirs[ "Lua" ] = "%{wks.location}/Thirdparty/"
IncludeDirs[ "MicroTest" ] = "%{wks.location}/MicroTest/"
IncludeDirs[ "MicroLua" ] = "%{wks.location}/MicroLua/"
