#include <nan.h>
#include <errno.h>
#include <string>

#include <unistd.h>
#include <linux/memfd.h>

using namespace v8;

//const char* ToCString(Local<String> str) {
//	return *value(str);
//}

NAN_METHOD(memfd_create_nan) {

	Nan::HandleScope();
	if (info.Length() < 2 || info.Length() > 2) {
		return Nan::ThrowError(
			"memfd_create() takes 2 arguments: (name:string, flags:int)"
		);
	}

	// Try to be a little (motherly) helpful to us poor clueless developers
	if (!info[0]->IsString())	return Nan::ThrowError("memfd_create: name (arg[0]) must be a string");
	if (!info[1]->IsNumber())	return Nan::ThrowError("memfd_create: flags (arg[1]) must be an integer");
	const char * name = *info[0]->ToString()->Value();
	const unsigned int flags = info[1]->ToInteger()->Value();

	const int fd = memfd_create(name, flags);
	info.GetReturnValue().Set(Nan::New(fd));
}

void Init(Handle<Object> exports, Handle<Object> module) {
	constexpr auto property_attrs = static_cast<PropertyAttribute>(ReadOnly | DontDelete);
	Nan::DefineOwnProperty(exports, Nan::New("memfd_create").ToLocalChecked(), Nan::New<FunctionTemplate>(memfd_create_nan)->GetFunction(), property_attrs);

	auto set_int_prop = [&](const char* key, int val) -> void {
		Nan::DefineOwnProperty(exports, Nan::New(key).ToLocalChecked(), Nan::New(val), property_attrs);
	};
	set_int_prop("MFD_CLOEXEC", MFD_CLOEXEC);
	set_int_prop("MFD_ALLOW_SEALING", MFD_ALLOW_SEALING);
	set_int_prop("MFD_HUGETLB", MFD_HUGETLB);
	set_int_prop("MFD_HUGE_2MB", MFD_HUGE_2MB);
	set_int_prop("MFD_HUGE_16GB", MFD_HUGE_16GB);
}

NODE_MODULE(memfd_create, Init)
