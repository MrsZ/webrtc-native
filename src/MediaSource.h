/*
* The MIT License (MIT)
*
* Copyright (c) 2015 vmolsa <ville.molsa@gmail.com> (http://github.com/vmolsa)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#ifndef WEBRTC_MEDIASOURCE_H
#define WEBRTC_MEDIASOURCE_H

#include "Common.h"
#include "Thread.h"
#include "MediaStream.h"
#include "MediaStreamTrack.h"

namespace WebRTC { 
  enum MediaSourceEvent {
    kMediaSourceEnd = 1,
    kMediaSourceFrame,
  };
 
  class MediaSource : public RTCWrap, public EventEmitter { 
    public:
      explicit MediaSource();
      virtual ~MediaSource();
      
      static void Init(v8::Handle<v8::Object> exports);

      bool Connect(MediaSource *source = 0);
      bool Disconnect(MediaSource *source = 0);
      
      virtual void End();
      virtual bool End(v8::Local<v8::Value> data);
      virtual bool Write(v8::Local<v8::Value> data);
      
    private:
      static void New(const Nan::FunctionCallbackInfo<v8::Value> &info);
      static void Connect(const Nan::FunctionCallbackInfo<v8::Value> &info);
      static void Disconnect(const Nan::FunctionCallbackInfo<v8::Value> &info);
      static void Write(const Nan::FunctionCallbackInfo<v8::Value> &info);
      static void End(const Nan::FunctionCallbackInfo<v8::Value> &info);

      static void OnData(v8::Local<v8::String> property, const Nan::PropertyCallbackInfo<v8::Value> &info);
      static void OnError(v8::Local<v8::String> property, const Nan::PropertyCallbackInfo<v8::Value> &info);
      static void OnEnd(v8::Local<v8::String> property, const Nan::PropertyCallbackInfo<v8::Value> &info);    

      static void OnData(v8::Local<v8::String> property, v8::Local<v8::Value> value, const Nan::PropertyCallbackInfo<void> &info);
      static void OnError(v8::Local<v8::String> property, v8::Local<v8::Value> value, const Nan::PropertyCallbackInfo<void> &info);
      static void OnEnd(v8::Local<v8::String> property, v8::Local<v8::Value> value, const Nan::PropertyCallbackInfo<void> &info);
      
      virtual void On(Event *event);
      
    protected:
      bool _closing;
      bool _callback;
      
      Nan::Persistent<v8::Function> _ondata;
      Nan::Persistent<v8::Function> _onerror;
      Nan::Persistent<v8::Function> _onend;
      
      static Nan::Persistent<v8::Object> constructor;
  };
};

#endif