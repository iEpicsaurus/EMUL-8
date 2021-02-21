#include <string>
#include <vector>

/**
* @brief Deals with the memory of the CHIP-8 emulator
*
* The creation of the Emulator memory system used to read, and write via other classes
 *
 * @author James Mitsumasu
 *
*/
class EmuMemory
{
	public:
	
		/// Default constructor
		EmuMemory(std::string filename);
		
		/// Reads a byte at the specified address
		uint8_t read(uint16_t addr);
		
		/// Read amount of bytes specified starting at location addr and returns as a vector of uint8_t
		std::vector<uint8_t> read_bytes(uint16_t addr, uint16_t amount);
		
		/// Store a byte at the the next open address location
		void write(uint16_t addr, uint8_t data);
		
		/// Store x amount of bytes at the next available location
		void write_bytes(uint16_t addr, std::vector<uint8_t> value);
		
	private:
		
		/// Check bounds of memory
		void mem_check(uint16_t addr);
		
		/// An array of bytes specifying the memory map 
		uint8_t ram[4096] = {};
};
