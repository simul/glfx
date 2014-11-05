glfx
====

This is Simul's branch of glfx. Initially I created it to keep track of any minor adaptations I needed to make to compile with our setup. Now though it's a proper branch with new features.

Preprocessing
-------------
It's hard to adapt or use existing shaders without support for preprocessing - in particular, we want to suport #include, #define, #ifdef, #ifndef, #else, #endif, and #if.

So I've added a separate preprocessing step; this uses flex and bison just like the main effect processor, but with a separate implementation.

Techniques
----------
One thing we're trying to achieve here is to create a framework for a .glfx effect format that tracks Microsoft's .fx files for hlsl. That means allowing *techniques* to be defined. Where base glfx defines GLSL-style programes like:

	program my_prog
	{
	    vs(430) = VS_Font();
	    fs(430) = PS_Font();
	};

We want to split things into *techniques*, composed of one or more *passes*:

	technique test_tech
	{
		pass p0
		{
			vs(430) = VS_Font();
			fs(430) = PS_Background();
		}
		pass p1
		{
			vs(430) = VS_Font();
			fs(430) = PS_Font();
		}
	}
	
The closer we can get glfx to hlsl fx, the more common code we can use.
