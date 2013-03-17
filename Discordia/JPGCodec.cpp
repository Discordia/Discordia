#include "JPGCodec.h"
#include "Surface.h"

namespace Discordia
{
	namespace Graphics
	{
		JPGCodec::JPGCodec()
			: ISurfaceCodec()
		{
		}

		JPGCodec::~JPGCodec()
		{
		}

		bool JPGCodec::CanDecodeSurface(IO::IFileReader* fileReader)
		{
			string fileEnd = fileReader->GetFileName().substr(fileReader->GetFileName().length()-4);
			if ( fileEnd == ".JPG" || fileEnd == ".jpg")
				return true;

			return false;
		}

		void JPGCodec::InitSource (j_decompress_ptr cinfo)
		{

		}

		void JPGCodec::TermSource (j_decompress_ptr cinfo)
		{
		}

		void JPGCodec::SkipInputData(j_decompress_ptr cinfo, long count)
		{
			jpeg_source_mgr * src = cinfo->src;
			if(count > 0)
			{
				src->bytes_in_buffer -= count;
				src->next_input_byte += count;
			}
		}

		u8 JPGCodec::FillInputBuffer (j_decompress_ptr cinfo)
		{
			// DO NOTHING
			return 1;
		}

		ISurface* JPGCodec::Decode(IO::IFileReader* fileReader)
		{
			fileReader->Seek(0, std::ios::beg);
			u8* input = new u8[fileReader->GetSize()];
			fileReader->Read((c8*)input, fileReader->GetSize());

			struct jpeg_decompress_struct cinfo;
			struct jpeg_error_mgr jerr;

			// Error handling
			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_decompress(&cinfo);

			jpeg_source_mgr jsrc;
			jsrc.bytes_in_buffer = fileReader->GetSize();
			jsrc.next_input_byte = (JOCTET*)input;
			cinfo.src = &jsrc;

			jsrc.init_source = InitSource;
			jsrc.fill_input_buffer = FillInputBuffer;
			jsrc.skip_input_data = SkipInputData;
			jsrc.resync_to_restart = jpeg_resync_to_restart;
			(void) jpeg_read_header(&cinfo, TRUE);
			jsrc.term_source = TermSource;

			//Start decompression
			(void) jpeg_start_decompress(&cinfo);

			// Get image data
			u16 rowspan = cinfo.image_width * cinfo.num_components;
			unsigned width = cinfo.image_width;
			unsigned height = cinfo.image_height;

			bool has_alpha= false;
			bool greyscale;

			if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
				greyscale = true;
			else
				greyscale = false;

			// Allocate memory for buffer
			u8 *output = new u8[rowspan * height];

			u8 **rowPtr = new u8 * [height];
			for( unsigned i = 0; i < height; i++ )
				rowPtr[i] = &output[ i * rowspan ];

			unsigned rowsRead = 0;
			while( cinfo.output_scanline < cinfo.output_height )
				rowsRead += jpeg_read_scanlines( &cinfo, &rowPtr[rowsRead], cinfo.output_height - rowsRead );

			delete[] rowPtr;

			(void) jpeg_finish_decompress(&cinfo);

			// Decompression finished
			jpeg_destroy_decompress(&cinfo);


			ISurface* surface = new Surface(COLOR_R8G8B8, Dimension2D<s32>(width, height), output);
			delete[] input;
			return surface;
		}
	}
}