# Comments from Hurubon

## Me

Hi, I would appreciate some feedback on this C implementation of a singly linked list. I use C89 just for the challenge.
I had a uni assignment, in which I had to do it in Java, but I hate Java and I was curious to see how good/bad my C implementation is.
I'm looking for:
- advices about bad/good practices
- about my error handling
- if there's a better way to write ll_printf()

https://github.com/sebastka/DataStructures/tree/master/linkedlist/src

## Hurubon

Hey. I'm also a C enthusiast who wanted to learn the language similarly to your method, so I'm always happy to see those who share my interests.

The linked list implementation was also my first C project, and I can see that yours suffers from similar mistakes.

1) **Constructors**:
    Why is the linked list object itself on the heap? I don't see a need for this in general, and the interface could be adapted to be agnostic and not care about where the linked list is.
2) **OOP**:
    The insistence on object-orientation and OOP concepts is perhaps intuitive to someone learning Java, but it isn't from a C perspective. C is a procedural language, so it plays better with procedural code, but it also often allows implementations to be better than their OOP counterparts. OOP itself is actually not as broad of a paradigm as one might be lead to believe. Like all tools, it's limited to its effective use-cases.
3) **Namespacing**:
    This might not be relevant to the project at hand, but is useful to know in general. The way you namespace your library (the ll_ prefix) is quite ugly in my opinion. The character 'l' itself looks pretty bad with most text editor fonts, resembles other symbols like I and 1 and overall just sucks. Also, the fact that it's 'll' and not, say 'linkedlist' makes it slightly less clear and ends up looking lazy. We aren't restricted to 8 character identifiers anymore, go crazy.
4) **Assertions**:
    In your code, I often see patterns like:
	 ```c
	 if (!linkedlist)
    _ERR("Error in ll_count(): nullptr passed as argument\n", FALSE);
	```
	These could easily be replaced with assert() or or even something more abstract that better explains what you meant. Side note: using operator! on non-booleans is considered bad practice.

	Here's a utility macro I found in someone else's code from this server:
	```c
	#define assuming(x) \
    	assert(x);      \
    	if (x)
	```

	Leveraging this macro, you could reformat your code to be:
	```c
	struct Linkedlist* ll_create(void) {
        /* Note: double type dependency.*/
    	struct Linkedlist* linkedlist = calloc(1, sizeof(struct Linkedlist);
    	assuming(linkedlist != NULL) {
            /* Note: this is pointless if you use calloc.*/
            linkedlist->head = NULL;
        }    
    	return linkedlist;
	}
	```
	Cleaning up the notes in the comments, we get:
	```c
	struct Linkedlist* ll_create(void) {
		struct Linkedlist* linkedlist = calloc(1, sizeof *linkedlist);
    	assert(linkedlist != NULL);
    	return linkedlist;
	}
	```
5) **Custom booleans**:
    We know C89 didn't have booleans, so it doesn't make much sense to pretend it does or implement your own. At that time, most people used integer-valued functions returning 0 or 1 to indicate false and true respectively. This is fine because it's compatible with C99+ code. Your macros are more likely to cause harm than good, as most things related to the preprocessor.
6) **Type erasure**:
    I see that you leveraged void pointers to achieve type erasure, or effectively a generic linked list. However, this is a horrible way to implement type erasure because it requires two levels of indirection to reach the actual value. There are better ways to do it using polymorphism and inheritance.
7) **Algorithm complexity and sentinel nodes**:
    The agorithm for inserting a node is very complex and inefficient. This is because it has to handle many edge cases due to the list itself not being bound by sentinel nodes. The algorithm complexity could be reduced massively by employing this technique.
8) **Top-level const overuse**:
    There are many occurrences of top-level const overuse, which just makes the code harder to read, more bloated and likely adds nothing in terms of efficiency. This is usually not needed unless you're passing pointers of some function arg to a different function and don't want it to be changed accidentally (also enables optimizations).

## Me

Whoa thanks, I did not expect such an extensive answer! I will adapt my code according to your comments.
Two remarks:
- Point 2) Appart from two comments in my code mentioning opp concepts, do you think I am trying to apply some in my code?
- Point 4) That's an interesting solution, though assert will always stop the execution of the code. In some cases, I would prefer the program to just continue. I'm inclined to try to use both, unless there is a reason not too?

## Hurubon

- Point 2) It just gives me that sort of vibe. It seems like it was written from an OOP standpoint, but with all the OOP features being unavailable, so it ends up highly conflicted and dissonant. It's better to think in a procedural style (not just in C, but in general) in my opinion.
- Point 4) If calloc fails, you don't really have a choice but to kill your program. Also, asserts enable optimizations.


	I don't see why you would not want to crash a program if it passes you a NULL linked list pointer.

	Crashing programs motivates programmers to actually fix mistakes.

## Me

Yep right. Also, you mention polymorphism and inheritance. In C?

## Hurubon

Yes.
I was just going to talk about that.
If you want to see a streamlined linked list implementation in C, take a loot at the Linux one, the PintOS one, or my own which I adapted and simplified from PintOS (uses polymorphism to be type-generic): https://github.com/Hurubon/pnk-linked-list

```c
struct test
{
    struct pnk_list_elem elem;
    int dummy;
};
```
This `pnk_list_elem` is the key thing to polymorphism.

This leverages the fact that a pointer to a `struct test` is also a pointer to a `struct pnk_list_elem`, so any function which takes a `struct pnk_list_elem*` can also take a struct `test*`. You could say `struct test` "inherits" from `struct pnk_list_elem`.

And indeed this is true for any struct which follows this contract, even for arbitrary user-defined types.
This also allows for nodes which are not on the heap.

Which your impl does not.

Truly makes the list be "just a container" and not an "object manager". The user controls the lifetime.

## Me

Aha, alright. I haven't done anything like this before, so I'll have too look closely at your examples. And probably read you sentences about ten times more.

## Vin¢

the real weakness is not accepting the reality that some shit just aint meant to be

## Hurubon

C can do this, and it is meant to be.
There are things that aren't, though.
Can C do TMP? Nope. Can C be generic and provide abstractions? Yes.

## Vin¢

badly
you can do most things in most languages if you really want, but it’s more a question of picking a good tool for the job
i’m not trying to start a language war, but i still think it’s a relevant point to make

if you’re dead set on C, carefully consider the tradeoffs of a macro based approach and a void*/runtime based approach
_Generic can occasionally help too