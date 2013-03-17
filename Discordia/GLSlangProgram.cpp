#include <gl/GLee.h>
#include "GLSlangProgram.h"

namespace Discordia
{
	namespace Graphics
	{
		GLSlangProgram::GLSlangProgram()
			: IGPUProgram(), programId(0), isLinked(false)
		{
			programId = glCreateProgramObjectARB();
		}

		GLSlangProgram::~GLSlangProgram()
		{
			glUseProgramObjectARB(0);
			glDeleteObjectARB(programId);
		}

		void GLSlangProgram::AttachShader(shared_ptr<IShaderObject> shader)
		{
			glAttachObjectARB(programId, shader->GetShaderId());
			shaders.push_back(shader);
		}

		bool GLSlangProgram::LinkProgram()
		{
			if (isLinked)
			{
				for (u32 i = 0; i < shaders.size(); i++)
					glDetachObjectARB(programId, shaders[i]->GetShaderId());

				isLinked = false;
			}
		
			s32 linked;
			glLinkProgramARB(programId);
			glGetObjectParameterivARB(programId, GL_OBJECT_LINK_STATUS_ARB, &linked);

			if (linked)
			{
				isLinked = true;
				return true;
			}

			return false;
		}

		bool GLSlangProgram::IsLinked()
		{
			return isLinked;
		}

		bool GLSlangProgram::Begin()
		{
			if (programId == 0 || !isLinked)
				return false;

			glUseProgramObjectARB(programId);
			return true;
		}

		void GLSlangProgram::End()
		{
			glUseProgramObjectARB(0);
		}

		bool GLSlangProgram::SendUniform1f(c8* varname, f32 v0)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform1fARB(loc, v0);
			return true;
		}

		bool GLSlangProgram::SendUniform2f(c8* varname, f32 v0, f32 v1)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform2fARB(loc, v0, v1);
			return true;
		}

		bool GLSlangProgram::SendUniform3f(c8* varname, f32 v0, f32 v1, f32 v2)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform3fARB(loc, v0, v1, v2);
			return true;
		}

		bool GLSlangProgram::SendUniform4f(c8* varname, f32 v0, f32 v1, f32 v2, f32 v3)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform4fARB(loc, v0, v1, v2, v3);
			return true;
		}

		bool GLSlangProgram::SendUniform1i(c8* varname, s32 v0)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform1iARB(loc, v0);
			return true;
		}

		bool GLSlangProgram::SendUniform2i(c8* varname, s32 v0, s32 v1)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform2iARB(loc, v0, v1);
			return true;
		}

		bool GLSlangProgram::SendUniform3i(c8* varname, s32 v0, s32 v1, s32 v2)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform3iARB(loc, v0, v1, v2);
			return true;
		}

		bool GLSlangProgram::SendUniform4i(c8* varname, s32 v0, s32 v1, s32 v2, s32 v3)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform4iARB(loc, v0, v1, v2, v3);
			return true;
		}

		bool GLSlangProgram::SendUniform1fv(c8* varname, s32 count, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform1fvARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform2fv(c8* varname, s32 count, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform2fvARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform3fv(c8* varname, s32 count, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform3fvARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform4fv(c8* varname, s32 count, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform4fvARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform1iv(c8* varname, s32 count, s32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform1ivARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform2iv(c8* varname, s32 count, s32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform2ivARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform3iv(c8* varname, s32 count, s32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform3ivARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniform4iv(c8* varname, s32 count, s32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniform4ivARB(loc, count, value);
			return true;
		}

		bool GLSlangProgram::SendUniformMatrix2fv(c8* varname, s32 count, bool transpose, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniformMatrix2fvARB(loc, count, transpose, value);
			return true;
		}

		bool GLSlangProgram::SendUniformMatrix3fv(c8* varname, s32 count, bool transpose, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniformMatrix3fvARB(loc, count, transpose, value);
			return true;
		}

		bool GLSlangProgram::SendUniformMatrix4fv(c8* varname, s32 count, bool transpose, f32 *value)
		{
			s32 loc = GetUniformLoc(varname);

			if (loc == -1) 
				return false;

			glUniformMatrix4fvARB(loc, count, transpose, value);
			return true;
		}

		void GLSlangProgram::GetUniformfv(c8* name, f32* values)
		{
			s32 loc;
			loc = glGetUniformLocationARB(programId, name);
			glGetUniformfvARB(programId, loc, values);
		}

		void GLSlangProgram::GetUniformiv(c8* name, s32* values)
		{
			s32 loc;

			loc = glGetUniformLocationARB(programId, name);
			glGetUniformivARB(programId, loc, values);
		}

		s32 GLSlangProgram::GetUniformLoc(const c8* name)
		{
			return glGetUniformLocationARB(programId, name);
		}
	}
}