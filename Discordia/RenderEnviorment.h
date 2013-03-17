#ifndef RENDER_ENVIORMENT_H_INCLUDED
#define RENDER_ENVIORMENT_H_INCLUDED

#include "Dimension2D.h"
#include "Types.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 * Holds multiple viewports.
		 * TODO: This is ugly, should hold one and render enviorment should hold a list
		 *       if there where to be more viewports. Anyway this is not used today.
		 */
		class Viewports
		{
		public:
			Viewports()
				: nrViewports(1)
			{
				viewports = new s32[4];
				viewports[0] = 0; viewports[1] = 0;
				viewports[2] = 1; viewports[3] = 1;
			}

			~Viewports()
			{
				delete[] viewports;
			}

			s32 nrViewports;
			s32* viewports;
		};

		/** 
		 *	Class that holds information about the render enviorment, for the moment the screen size 
		 *  and how many viewports.
		 */
		class RenderEnviorment
		{
		public:
			RenderEnviorment(const Dimension2D<s32>& screenDim, Viewports* viewports)
				: screenDim(screenDim), viewports(viewports)
			{
			}

			~RenderEnviorment() {}

			const Dimension2D<s32>& GetScreenDim() const 
			{ 
				return screenDim; 
			}

			const Viewports* GetViewports()
			{
				return viewports;
			}

		private:
			Dimension2D<s32>	screenDim;
			Viewports*			viewports;
		};
	}
}


#endif