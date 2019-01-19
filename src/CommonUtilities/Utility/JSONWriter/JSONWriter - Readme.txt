What is JSONWriter?
	JSONWriter is a helper class to create .json files through c++. 

How do I use it?
	Step 1:
		Create a JSONWriter object!
	Step 2:
		Call Begin() and give a filename as argument
	Step 3:
		Create arrays, objects, members or values! It follows the same rules as json does, so it will tell you if you do something wrong!
	Step 4:
		Call End()! This will also write to the file.

What are the types and how does it work?
	arrays = []. These can only hold unnamed values
	objects = {}. You are in an object after Begin().
	members = "member name" : "member value". You can only create members when in an object.
	values = "value". You can only create values when in an array.

Tip!
	Use scopes to keep track of ArrayBegin(), ArrayEnd(), ObjectBegin() and ObjectEnd()s! This will be much easier on the eyes!

