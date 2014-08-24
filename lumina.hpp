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
#include "config/BaseProxy.hpp"
#include "config/ContextProxy.hpp"
#include "config/LConfig.hpp"

// include core components
#include "core/LogLevel.hpp"
#include "core/LuminaException.hpp"
#include "core/ServiceContext.hpp"

// include input components
#include "input/InputEvent.hpp"
#include "input/KeyCode.hpp"
#include "input/WindowEvent.hpp"

// include io components
#include "io/Image.hpp"
#include "io/ImageJPEG.hpp"
#include "io/ImagePNG.hpp"

// include scene components
#include "scene/scene.hpp"

// include service components
#include "service/Logger.hpp"
#include "service/ServiceProvider.hpp"
#include "service/StaticLogger.hpp"

// include video.hpp -> includes more files
#include "video/video.hpp"

 // include utility types
#include "util/util.hpp"


// namespace alias
namespace lum = lumina;
