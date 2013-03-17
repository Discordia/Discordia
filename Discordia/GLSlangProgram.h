#ifndef IGPU_PROGRAM_H_INCLUDED
#define IGPU_PROGRAM_H_INCLUDED

#include <vector>
#include "IGPUProgram.h"

using std::vector;

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  GLSL shader program, should have at least one pixel and one vertex shader attached to it.
		 *  Can have more than one though (as long as only one vertex and one pixel shader has a main 
		 *  function).
		 */
		class GLSlangProgram : public IGPUProgram
		{
		public:
			GLSlangProgram();
			virtual ~GLSlangProgram();

			u32  GetProgramId() { return programId; }
			void AttachShader(shared_ptr<IShaderObject> shader);
			bool LinkProgram();
			bool IsLinked();

			bool Begin();
			void End();

			bool SendUniform1f(c8* varname, f32 v0);
			bool SendUniform2f(c8* varname, f32 v0, f32 v1); 
			bool SendUniform3f(c8* varname, f32 v0, f32 v1, f32 v2);
			bool SendUniform4f(c8* varname, f32 v0, f32 v1, f32 v2, f32 v3);

			bool SendUniform1i(c8* varname, s32 v0);
			bool SendUniform2i(c8* varname, s32 v0, s32 v1);
			bool SendUniform3i(c8* varname, s32 v0, s32 v1, s32 v2);
			bool SendUniform4i(c8* varname, s32 v0, s32 v1, s32 v2, s32 v3);

			bool SendUniform1fv(c8* varname, s32 count, f32 *value);
			bool SendUniform2fv(c8* varname, s32 count, f32 *value);
			bool SendUniform3fv(c8* varname, s32 count, f32 *value);
			bool SendUniform4fv(c8* varname, s32 count, f32 *value);

			bool SendUniform1iv(c8* varname, s32 count, s32 *value);
			bool SendUniform2iv(c8* varname, s32 count, s32 *value);
			bool SendUniform3iv(c8* varname, s32 count, s32 *value);
			bool SendUniform4iv(c8* varname, s32 count, s32 *value);

			bool SendUniformMatrix2fv(c8* varname, s32 count, bool transpose, f32 *value);
			bool SendUniformMatrix3fv(c8* varname, s32 count, bool transpose, f32 *value);
			bool SendUniformMatrix4fv(c8* varname, s32 count, bool transpose, f32 *value);

			void GetUniformfv(c8* name, f32* values);
			void GetUniformiv(c8* name, s32* values); 

		protected:
			s32 GetUniformLoc(const c8* name);

		protected:
			vector<shared_ptr<IShaderObject> > shaders;
			u32 programId;
			bool isLinked;
		};

	}
}


#endif