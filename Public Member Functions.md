Public Member Functions

		V8EXPORT bool 	BooleanValue () const
		V8EXPORT bool 	Equals (Handle< Value > that) const
		 	JS ==. 
		V8EXPORT int32_t 	Int32Value () const
		V8EXPORT int64_t 	IntegerValue () const
		V8EXPORT bool 	IsArray () const
		 	Returns true if this value is an array. 
		V8EXPORT bool 	IsBoolean () const
		 	Returns true if this value is boolean. 
		V8EXPORT bool 	IsBooleanObject () const
		 	Returns true if this value is a Boolean object. 
		V8EXPORT bool 	IsDate () const
		 	Returns true if this value is a Date. 
		V8EXPORT bool 	IsExternal () const
		 	Returns true if this value is external. 
		V8EXPORT bool 	IsFalse () const
		 	Returns true if this value is false. 
		V8EXPORT bool 	IsFunction () const
		 	Returns true if this value is a function. 
		V8EXPORT bool 	IsInt32 () const
		 	Returns true if this value is a 32-bit signed integer. 
		V8EXPORT bool 	IsNativeError () const
		 	Returns true if this value is a NativeError. 
		V8EXPORT bool 	IsNull () const
		 	Returns true if this value is the null value. 
		V8EXPORT bool 	IsNumber () const
		 	Returns true if this value is a number. 
		V8EXPORT bool 	IsNumberObject () const
		 	Returns true if this value is a Number object. 
		V8EXPORT bool 	IsObject () const
		 	Returns true if this value is an object. 
		V8EXPORT bool 	IsRegExp () const
		 	Returns true if this value is a RegExp. 
		bool 	IsString () const
		 	Returns true if this value is an instance of the String type. 
		V8EXPORT bool 	IsStringObject () const
		 	Returns true if this value is a String object. 
		V8EXPORT bool 	IsTrue () const
		 	Returns true if this value is true. 
		V8EXPORT bool 	IsUint32 () const
		 	Returns true if this value is a 32-bit unsigned integer. 
		V8EXPORT bool 	IsUndefined () const
		 	Returns true if this value is the undefined value. 
		V8EXPORT double 	NumberValue () const
		V8EXPORT bool 	StrictEquals (Handle< Value > that) const
		V8EXPORT Local< Uint32 > 	ToArrayIndex () const
		 	Attempts to convert a string to an array index. 
		V8EXPORT Local< Boolean > 	ToBoolean () const
		V8EXPORT Local< String > 	ToDetailString () const
		V8EXPORT Local< Int32 > 	ToInt32 () const
		V8EXPORT Local< Integer > 	ToInteger () const
		V8EXPORT Local< Number > 	ToNumber () const
		V8EXPORT Local< Object > 	ToObject () const

When you are browsing http://izs.me/v8-docs/classv8_1_1Value.html#pub-methods V8EXPORT types are C++ types. Or at least interpratable by C++
