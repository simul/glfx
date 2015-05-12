glfx
====

This is Simul's branch of glfx. Initially I created it to keep track of any minor adaptations I needed to make to compile with our setup.
Now though it's a proper branch with new features.

Preprocessing
-------------
It's hard to adapt or use existing shaders without support for preprocessing - in particular, we want to suport #include, #define, #ifdef, #ifndef, #else, #endif, and #if.

So I've added a separate preprocessing step; this uses flex and bison just like the main effect processor, but with a separate implementation.
This means that in compiling a shader we're actually preprocessing twice: the effect compiler preprocesses before creating the individual shader source texts;
then the driver-internal GLSL compiler does its own limited preprocessing (for instance, #include is not supported in the GLSL standard).
We can't simply pass-through the preprocessor commands because we may have #includes within #ifdef blocks, and including everything may cause the GLSL compiler to fail - for example some compilers don't want to see a *discard* keyword within the source of a fragment shader, even if the function containing it is not invoked.
So we must preprocess the effect file if we're using preprocessor commands.

We also want sensible error messages, which point out the correct source filename and line number.
Again, the GLSL standard is in the way.
We can use the #line directive to tell the GLSL compiler where we are in the original (before preprocessing) source, but the standard only supports the style:

	#line 1 2
	
i.e. line 1 of **file** 2 - we can't specify filenames because the GLSL standard does not support that.
So we build up a list of filenames, starting from the original file and inserting each #included source file.
We insert a #line directive whenever code is snipped, inserted or rearranged by the preprocessor.
Later, if an error or warning is reported, we text-replace the file number with the corresponding filename.

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
