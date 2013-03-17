#ifndef IGPU_PROGRAM_H_NICLUDED
#define IGPU_PROGRAM_H_NICLUDED

#include <memory>
#include "Types.h"
#include "IShaderObject.h"

using std::shared_ptr;

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  Interface that represents a Vertex program that changes the fixed graphic pipeline.
		 */
		class IGPUProgram
		{
		public:
			virtual ~IGPUProgram() {}

			virtual u32  GetProgramId() = 0;
			virtual void AttachShader(shared_ptr<IShaderObject> shader) = 0;
			virtual bool LinkProgram() = 0;
			virtual bool IsLinked() = 0;

			virtual bool Begin() = 0;
			virtual void End() = 0;

			virtual bool SendUniform1f(c8* varname, f32 v0) = 0;
			virtual bool SendUniform2f(c8* varname, f32 v0, f32 v1) = 0; 
			virtual bool SendUniform3f(c8* varname, f32 v0, f32 v1, f32 v2) = 0;
			virtual bool SendUniform4f(c8* varname, f32 v0, f32 v1, f32 v2, f32 v3) = 0;

			virtual bool SendUniform1i(c8* varname, s32 v0) = 0;
			virtual bool SendUniform2i(c8* varname, s32 v0, s32 v1) = 0;
			virtual bool SendUniform3i(c8* varname, s32 v0, s32 v1, s32 v2) = 0;
			virtual bool SendUniform4i(c8* varname, s32 v0, s32 v1, s32 v2, s32 v3) = 0;

			virtual bool SendUniform1fv(c8* varname, s32 count, f32 *value) = 0;
			virtual bool SendUniform2fv(c8* varname, s32 count, f32 *value) = 0;
			virtual bool SendUniform3fv(c8* varname, s32 count, f32 *value) = 0;
			virtual bool SendUniform4fv(c8* varname, s32 count, f32 *value) = 0;

			virtual bool SendUniform1iv(c8* varname, s32 count, s32 *value) = 0;
			virtual bool SendUniform2iv(c8* varname, s32 count, s32 *value) = 0;
			virtual bool SendUniform3iv(c8* varname, s32 count, s32 *value) = 0;
			virtual bool SendUniform4iv(c8* varname, s32 count, s32 *value) = 0;

			virtual bool SendUniformMatrix2fv(c8* varname, s32 count, bool transpose, f32 *value) = 0;
			virtual bool SendUniformMatrix3fv(c8* varname, s32 count, bool transpose, f32 *value) = 0;
			virtual bool SendUniformMatrix4fv(c8* varname, s32 count, bool transpose, f32 *value) = 0;

			virtual void GetUniformfv(c8* name, f32* values) = 0;
			virtual void GetUniformiv(c8* name, s32* values) = 0; 

		protected:
			IGPUProgram() {}
		};
	}
}

#endif