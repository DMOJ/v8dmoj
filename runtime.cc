// Copyright (c) 2015-2017 DMOJ: Modern Online Judge. All rights reserved.
// Copyright 2012 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "v8dmoj.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

// The callback that is invoked by v8 whenever the JavaScript 'quit'
// function is called.  Quits.
static void Quit(const v8::FunctionCallbackInfo<v8::Value> &args) {
  // If not arguments are given args[0] will yield undefined which
  // converts to the integer value 0.
  int exit_code =
      args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);

  std::fflush(stdout);
  std::fflush(stderr);
  std::exit(exit_code);
}

void Version(const v8::FunctionCallbackInfo<v8::Value> &args) {
  args.GetReturnValue().Set(v8::String::NewFromUtf8(args.GetIsolate(),
                                                    v8::V8::GetVersion(),
                                                    v8::NewStringType::kNormal)
                                .ToLocalChecked());
}

void Sleep(const v8::FunctionCallbackInfo<v8::Value> &args) {
  int ms =
      args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
  std::chrono::milliseconds duration(ms);
  std::this_thread::sleep_for(duration);
}

void InitializeRuntimeModule(v8::Isolate *isolate,
                             v8::Local<v8::ObjectTemplate> &global) {
  // Bind the 'quit' function
  global->Set(
      v8::String::NewFromUtf8(isolate, "quit", v8::NewStringType::kNormal)
          .ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, Quit));

  // Bind the 'version' function
  global->Set(
      v8::String::NewFromUtf8(isolate, "version", v8::NewStringType::kNormal)
          .ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, Version));

  // Bind the 'sleep' function
  global->Set(
      v8::String::NewFromUtf8(isolate, "sleep", v8::NewStringType::kNormal)
          .ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, Sleep));
}
