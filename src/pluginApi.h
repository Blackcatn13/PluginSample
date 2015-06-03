/*
 The MIT License (MIT)

 Copyright (c) 2015 Blackcatn13

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef SRC_PLUGINAPI_H_
#define SRC_PLUGINAPI_H_

class BasePlugin;

#define PLUGIN_API_VERSION 1

typedef BasePlugin *(*GetPluginFunc)();

struct PluginInfo {
  int apiVersion;                   // Version of the api used in this plugin
  const char *fileName;             // Name of the file
  const char *className;            // Name of the class in the plugin
  const char *pluginName;           // Name of the plugin
  const char *pluginVersion;        // Version of the plugin
  const char *pluginDescription;    // Small description of the plugin
  GetPluginFunc getPlugin;          // Function that initializes the plugin
};

#define NEW_PLUGIN(classType, pluginName, pluginVersion, pluginDescription)   \
  extern "C" {                                                                \
    BasePlugin* initPlugin()                                                  \
    {                                                                         \
      static classType m_singleton;                                           \
      return &m_singleton;                                                    \
    }                                                                         \
    PluginInfo information =                                                  \
    {                                                                         \
      PLUGIN_API_VERSION,                                                     \
      __FILE__,                                                               \
      #classType,                                                             \
      pluginName,                                                             \
      pluginVersion,                                                          \
      pluginDescription,                                                      \
      initPlugin,                                                             \
    };                                                                        \
  }                                                                           \

#endif  // SRC_PLUGINAPI_H_
