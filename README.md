# 🌸 chText 🌸
chText is a string library for C++ that provides the `chText` type: a string type used just like regular C++ strings but with UTF-8 support.

## Why chText

C++ strings don't support UTF-8 characters out of the box. This results in code like `cout << "你好"[0];` outputing `?` instead of `你`, because `你` is made up of multiple bytes and not just one (that would map nicely into a char). This library aims to fix that.

## How to add chText to your project

Just add `include "chText.hpp"` to your souce file(s) and you are done.

## How do I use chText?

chText has been designed to be used just as you would use any other old C++ string (with a few, tiny differences):

```c++
chText chineseText = "你好";
cout << "Chinese: " << chineseText << endl;
cout << "First letter: " << chineseText[0] << endl;
cout << ((chText)"你好!")[0] << endl;
cout << (chText) "你好!" + " How are you?" << endl;
//Etc.
```

There are four differences (that I can think of) with regular C++ strings:
 - When using the `[]` operator with a chText, you get another chText as a result, not a char.
 - You cannot iterate over a chText using iterators nor for each loops.
 - In certain situations (like in `((chText)"你好!")[0]` above) you have to cast a regular string to chText in order for the UTF-8 stuff to work.
 - The `chText` type also includes a `loadFile` method to load a text file into a `chText`. You can use it like `chText myText.loadFile("myFile.txt");`. That method returns true if the file was successfully loaded (and false otherwise).
 
 ## License
This license has been created by Marín del Río and released under the MIT License. Use it however you like!
