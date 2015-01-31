#ifndef UTTTDATA_HPP
#define UTTTDATA_HPP


class UtttData {
public:
    void addDataEntry(std::vector<unsigned>& sequence, unsigned winner);

private:
    std::array<std::vector<std::array<std::array<float, 81>, 81>>,80> connections;
    std::vector<std::pair<std::vector<unsigned>, unsigned>> data;
};


#endif // UTTTDATA_HPP
