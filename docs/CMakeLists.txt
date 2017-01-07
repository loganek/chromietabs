configure_file(Doxyfile.in Doxyfile)

add_custom_target("documentation" doxygen Doxyfile)
