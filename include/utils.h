template <typename T>
void showvalues(std::string title, T container, std::string separator = "")
{
    std::cout << title << "\n------------ " << title << " ------------" << std::endl;
    for(auto i : container)
    {
        std::cout << i << separator;
    }
    std::cout << "\n-------------------------------------------\n" << std::endl;
}