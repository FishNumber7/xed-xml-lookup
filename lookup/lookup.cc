extern "C" {
    #include "xed/xed-interface.h"
}

#include <cstring>
#include <iostream>
#include "pugixml.hh"

pugi::xml_document doc;
pugi::xml_parse_result result = doc.load_file("instructions.xml");
const char *arch = "";
std::string current_instruction  = "";

bool find_instruction(pugi::xml_node node) 
{
    return strcmp(node.attribute("iform").value(), current_instruction.c_str()) == 0;
}

bool find_arch(pugi::xml_node node)
{
    return strcmp(node.attribute("name").value(), arch) == 0;
}

bool find_uops(pugi::xml_attribute attr)
{
    return strcmp(attr.name(), "uops") == 0;
}

std::string decode(unsigned char itext[15]) {
    xed_machine_mode_enum_t mmode = XED_MACHINE_MODE_LONG_64;
    xed_address_width_enum_t stack_addr_width = XED_ADDRESS_WIDTH_64b;

    xed_tables_init();
 
    xed_error_enum_t xed_error;
    xed_decoded_inst_t xedd;
    xed_decoded_inst_zero(&xedd);
    xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);
    xed_error = xed_decode(&xedd, XED_STATIC_CAST(const xed_uint8_t*, itext), 15);
    
    return std::string(xed_iform_enum_t2str(xed_decoded_inst_get_iform_enum(&xedd)));
}

const char* lookup(unsigned char itext[15], const char* architecture)
{
    if (result) {
        current_instruction = decode(itext);
        arch = architecture;
        return doc.find_node(find_instruction).find_child(find_arch).first_child().find_attribute(find_uops).value();
    } else {
        return NULL;
    }
}

//example
/*int main() {
    unsigned char itext[15] = {0x48, 0x83, 0xec, 0x08};
    std::cout << decode(itext) << std::endl;
    std::cout << lookup(itext, "ZEN4") std::endl;
} */