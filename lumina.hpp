#pragma once
/**
 * \file lumina.hpp
 * Includes all other header of lumina and defines a namespace alias "lum" 
 * for lumina.
 * 
 * This file is part of the Lumina Graphics Library
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 */

// include config
#include "config/LConfig.hpp"

// include core components
#include "core/LuminaException.hpp"

// include input components
#include "input/KeyCode.hpp"
#include "input/InputEvent.hpp"

// include utility types
#include "util/util.hpp"

// include video.hpp -> includes more files
#include "video/video.hpp"

#include "scene/scene.hpp"

#include "io/Image.hpp"


// namespace alias
namespace lum = lumina;
