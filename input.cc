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

#include <cstdio>
#include <cstdlib>
#include <cstring>


// The callback that is invoked by v8 whenever the JavaScript 'gets'
// function is called.  Returns one line from stdin.
void Gets(const v8::FunctionCallbackInfo<v8::Value>& args) {
  int bufSize = 1024, valid = 0, extra = 1024;
  char *buffer = (char*) std::malloc(1024), *str = buffer;
  if (!buffer) {
    args.GetIsolate()->ThrowException(
        v8::String::NewFromUtf8(args.GetIsolate(), "Out of memory")
            .ToLocalChecked());
    return;
  }

  buffer[0] = 0;
  while (true) {
    if (std::fgets(str, extra, stdin) == NULL)
      break;
    valid += std::strlen(str);
    if (buffer[valid-1] == '\n')
      break;
    extra = bufSize;
    char *newBuf = (char*) std::realloc(buffer, bufSize *= 2);
    if (!newBuf) {
      args.GetIsolate()->ThrowException(
          v8::String::NewFromUtf8(args.GetIsolate(), "Out of memory")
              .ToLocalChecked());
      return;
    }
    buffer = newBuf;
    str = buffer + valid;
  }
  while (buffer[valid-1] == '\n' || buffer[valid-1] == '\r')
    --valid;
  args.GetReturnValue().Set(
      v8::String::NewFromUtf8(args.GetIsolate(), buffer, v8::NewStringType::kNormal, valid)
          .ToLocalChecked()
  );
  std::free(buffer);
}


void InitializeInputModule(v8::Isolate* isolate, v8::Local<v8::ObjectTemplate> &global) {
  // Bind the global 'gets' function to the C++ Gets callback.
  global->Set(v8::String::NewFromUtf8(
                  isolate, "gets", v8::NewStringType::kNormal).ToLocalChecked(),
              v8::FunctionTemplate::New(isolate, Gets));
}
