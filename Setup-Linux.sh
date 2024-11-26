#!/bin/bash

pushd ..

echo === Micro Core Setup ===

MicroCore/Build/Premake/Linux/premake5 --cc=clang --file=MicroCore/Build/Build.lua gmake2

popd
