# Events
Simple, C#-like events system

## Usage
1. Create a new event handler
```
struct KeyPressEventArgs : public Events::EventArgs {
	int key;
	int state;

	KeyPressEventArgs(int key, int state) {
		this->key = key;
		this->state = state;
	}
}

Events::Event<KeyPressEventArgs> keyPressEvent;
```
2. Add a callback:
```
keyPressEvent.bind([](const KeyPressEventArgs& args) {
	std::cout << "Key: " <<  args.key << " State: " << args.state;
});
```
or use the overloaded += operator.
```
keyPressEvent += [](const KeyPressEventArgs& args) {
	std::cout << "Key: " <<  args.key << " State: " << args.state;
};
```
3. Fire the event handler:
```
keyPressEvent.fire({ 65, 1 });
```
4. Remove a callback
```
Events::EventToken token = keyPressEvent.bind([](const KeyPressEventArgs& args) {
	std::cout << "Key: " <<  args.key << " State: " << args.state;
});
keyPressEvent.unbind(token);
```
or use the overloaded -= operator.
```
keyPressEvent -= token;
```

## License
```
MIT License

Copyright (c) 2018 Wojciech Grzeszczak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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
```
