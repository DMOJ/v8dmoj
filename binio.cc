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

#include <cstdint>
#include <cstdio>

// Read a specified number of bytes from stdin and return it as a Uint8Array.
static void Read(const v8::FunctionCallbackInfo<v8::Value> &args) {
  size_t bytes = (size_t)args[0]
                     ->IntegerValue(args.GetIsolate()->GetCurrentContext())
                     .FromMaybe(0);
  if (!bytes) {
    args.GetReturnValue().SetUndefined();
    return;
  }

  void *buffer = std::malloc(bytes);
  size_t read = std::fread(buffer, 1, bytes, stdin);
  auto result = v8::ArrayBuffer::New(args.GetIsolate(), read);
  memcpy(result->GetBackingStore()->Data(), buffer, read);
  args.GetReturnValue().Set(result);
  free(buffer);
}

static void Write(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Local<v8::ArrayBuffer> buffer;
  size_t offset, length;
  if (args[0]->IsArrayBufferView()) {
    auto view = v8::Handle<v8::ArrayBufferView>::Cast(args[0]);
    buffer = view->Buffer();
    offset = view->ByteOffset();
    length = view->ByteLength();
  } else if (args[0]->IsArrayBuffer()) {
    buffer = v8::Handle<v8::ArrayBuffer>::Cast(args[0]);
    offset = 0;
    length = buffer->ByteLength();
  } else {
    return;
  }

  std::fwrite((char *)buffer->GetBackingStore()->Data() + offset, 1, length, stdout);
  std::fflush(stdout);
}

void InitializeBinIOModule(v8::Isolate *isolate,
                           v8::Local<v8::ObjectTemplate> &global) {
  // Bind the global 'read' function to the C++ Read callback.
  global->Set(
      v8::String::NewFromUtf8(isolate, "read", v8::NewStringType::kNormal)
          .ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, Read));

  // Bind the global 'Write' function to the C++ Write callback.
  global->Set(
      v8::String::NewFromUtf8(isolate, "write", v8::NewStringType::kNormal)
          .ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, Write));
}
