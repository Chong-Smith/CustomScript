# CustomScript
Custom script implementation (parsing with flex and bison tools, custom instruction sets, and Qt-based instruction interpreters)

description：
Grammatical features
1. 3 Basic data type ：int(integer) , wchar( = QChar) ， wstring( = QString) ;
2. Support UTF-8 input ；
3. 5 Arithmetic operation : + , - , * , / , % ;
4. 2 Relational operation ：|| ， && ；
5. 2 Specific jump statement ：goup(level) , godown(level) ;
6. if(Conditional expression) statement ；
7. while(Conditional expression) statement ;
8. Unrestricted position declaration variable ；
9. Support fragment compilation and full compilation ；
10. Support for declaring 2-dimensional arrays ；
11. Support user to add functions (need to modify part of the code) ；
12. Support for passing parameters to functions ；


translater：
 1. Can generate custom three address codes ；
 2. Support for finding errors ；
 3. Support for data type checking ；
 4. Check for redeclaration errors ；
 5. Function parameter partial check ；
 6. Array subscript overflow is not supported (compilation phase) ；
 7. Except for 0 check (compilation phase) is not supported ；
