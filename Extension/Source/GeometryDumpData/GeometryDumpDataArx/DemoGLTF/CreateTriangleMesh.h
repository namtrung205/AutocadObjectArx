#pragma once
#include <GLTFSDK/GLTF.h>
#include <GLTFSDK/BufferBuilder.h>
#include <GLTFSDK/GLTFResourceWriter.h>
#include <GLTFSDK/GLBResourceWriter.h>
#include <GLTFSDK/IStreamWriter.h>
#include <GLTFSDK/Serialize.h>


#include <fstream>
#include <sstream>
#include <iostream>

#include <cassert>
#include <cstdlib>
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using namespace Microsoft::glTF;

namespace Demo
{
	void SerializeTriangle(const fs::path& path);

}