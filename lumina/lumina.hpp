#pragma once

// include config
#include "config/LConfig.hpp"

// include core components
#include "core/LException.hpp"
#include "core/LGLException.hpp"

// include input components
#include "input/LKeyCode.hpp"
#include "input/LInputEvent.hpp"

// include utility types
#include "util/half.hpp"            // 16 bit float type
#include "util/LVector.hpp"         // mathematical vector
#include "util/LMatrix.hpp"         // matrix
#include "util/LColor.hpp"          // color
#include "util/LTerminalColor.hpp"  // tools to write colored text to stdout

// include video.hpp -> includes more files
#include "video/video.hpp"