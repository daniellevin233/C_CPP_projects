#include <iostream>
#include <sstream>
#include<fstream>
#include<limits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

// -------------------------------- integer macros --------------------------------
#define NUMBER_OF_DIMENSIONS 3
#define GENERAL_FEATURES_NUM 4
#define DOUBLE_PRECISION 2
#define NOT_FOUND_INT (-1)

// -------------------------------- string macros --------------------------------
#define SEPARATOR_STR "-----"
#define CAT_NUM_STR "Item"
#define CAT_NAME_STR "Name"
#define QUANTITY_STR "Quantity"
#define PRICE_STR "Price"
#define WEIGHT_STR "Weight"
#define CALORIES_STR "Calories"
#define DIMENSIONS_STR "Dimensions"
#define MATERIAL_STR "Material"
#define COLOR_STR "Color"
#define CAPACITY_STR "Capacity"
#define AUTHOR_STR "Author"
#define PUBL_YEAR_STR "Year of publication"
#define LENGTH_STR "Length"
#define CANDY_ITEM_STR "Candy"
#define CLOTH_ITEM_STR "Cloth"
#define CROCKERY_ITEM_STR "Crockery"
#define FURNITURE_ITEM_STR "Furniture"
#define MEDIA_ITEM_STR "Media"

// -------------------------------- char macros --------------------------------
#define NEW_LINE_CHAR '\n'
#define SPACE_CHAR ' '
#define COLON_CHAR ':'

// -------------------------------- useful standard objects --------------------------------
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::move;

// -------------------------------- constant vectors - sets of features ---------------------------
const static vector<string> g_item_features = {CAT_NUM_STR, CAT_NAME_STR, QUANTITY_STR, PRICE_STR};
const static vector<string> g_cloth_add_features = {WEIGHT_STR};
const static vector<string> g_candy_add_features = {CALORIES_STR};
const static vector<string> g_furniture_add_features = {DIMENSIONS_STR, MATERIAL_STR, COLOR_STR};
const static vector<string> g_crockery_add_features = {DIMENSIONS_STR, CAPACITY_STR};
const static vector<string> g_media_add_features = {AUTHOR_STR, PUBL_YEAR_STR, LENGTH_STR};

/**
 * An item abstract class - an item in Ikea catalogue.
 */
class item
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor that gets the general features
     * @param id - int - id of the item in catalogue
     * @param name - string - the name of the item
     * @param price - double - price of the item
     * @param quantity - double - quantity of the item
     */
    explicit item(const int& id, string && name, const double& price, const double& quantity)
            : _id(id), _name(name), _price(price), _quantity(quantity) {};

    // -------------------------------- methods --------------------------------

    /**
     * Virtual method for printing item object, implemented in the inherited classes
     */
    virtual void print() const = 0;

    /**
     * Sell 'this' by decreasing its quantity field
     * @param quantity - quantity of units to be sold
     * @return true if item is sold and quantity decreased, false if there is no enough quantity
     */
    bool sellItem(double& quantity);

    // -------------------------------- operators --------------------------------

    /**
     * Compare two items by its id number (assumption that there are no two items with the same id
     * but different names
     * @param other_it - item to be compared to
     * @return - true if id of the items are equal, false otherwise
     */
    bool operator== (const item& other_it) const;

    /**
     * The opposite of the operator == :@see operator==
     */
    bool operator!= (const item& other_it) const;

    /**
     * Comparison if items based on the id number
     * @param other_it - item to be compared to
     * @return - true if id of 'this' smaller than if of other, false otherwise
     */
    bool operator< (const item& other_it) const;

    // -------------------------------- getters --------------------------------

    /**
     * Getter of the _id
     * @return - int - representing _id
     */
    int getCatNumber() const;

    /**
     * Getter of the _name
     * @return - to string - representing _name
     */
    string getCatName() const;

    /**
     * Getter of the _quantity
     * @return - double - representing _quantity
     */
    double getQuantity() const;

    // -------------------------------- setters --------------------------------

    /**
     * Setter for _quantity
     * @param new_quantity - double - new quantity to be set
     */
    void setQuantity(double new_quantity);

    // -------------------------------- destructor --------------------------------

    /**
     * Default virtual destructor for item
     */
    virtual ~item() = default;
protected:
    int _id; /**<_id - contains the number representing id in the catalogue*/
    string _name; /**<_name - contains the string representing the name of the item*/
    double _price; /**<_price - contains the double representing price of the item*/
    double _quantity; /**<_quantity - contains the double representing the quantity of the item*/
};

/**
 * Class representing Ikea catalogue with different items
 */
class catalogue
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Default constructor for catalogue (initialise empty data structure)
     */
    catalogue() = default;

    // -------------------------------- methods --------------------------------

    /**
     * Method adds item to the catalogue, in the case the item already exists in the catalogue,
     * its quantity will be increased, otherwise new item will be created and added
     * @param new_it - item to be added
     * @return - true if trying to add legal item - and it was successfully added, false otherwise
     */
    bool addItem(item* new_it, int item_cnt);

    /**
     * Method makes search of the item in the catalogue by given name, and return its index there
     * @param num - catalogue number of the item to be found
     * @return - NOT_FOUND_INT if the item with catalogue number num doen't contained in the
     * catalogue, otherwise index of the found item in the catalogue
     */
    int findByNumber(int && num) const;

    /**
     * @See findByNumber with find by name instead of number
     * @param name - catalogue name of the item to be found
     */
    int findByName(const string& name) const;

    /**
     * Method requests a catalogue number of the item from user, looking for it in the catalogue
     * and then if it was identified prints it to the standard out, else doing nothing
     */
    void printByInputNumber() const;

    /**
     * Method requests a catalogue name of the item from user, looking for it in the catalogue
     * and then if it was identified prints it to the standard out, else doing nothing
     */
    void printByInputName() const;

    /**
     * Function prints all the catalogue members (items) in the order they are appearing to te
     * current moment in the catalogue
     */
    void printCatalogueMembers() const;

    /**
     * print all the items from the catalogue in accordance to their names alphabetical order
     */
    void printByName();

    /**
     * Method prints all the items from the catalogue in accordance to their numbers order
     */
    void printByNumber();

    /**
     * Method sorts the catalogue items in accordance to their numbers order
     */
    void sortCatalogueByNum();

    /**
     * Method sorts the catalogue items in accordance to their names alphabetical order
     */
    void sortCatalogueByName();

    /**
     * Method request the catalogue number of the item to be sold, and sell it in the case of
     * enough quantity, otherwise doing nothing
     */
    void sellItem();

    // -------------------------------- operators --------------------------------

    /**
     * The [] operator for extracting the item from catalogue place "index"
     * @param index - place of the item to be extracted
     * @return - pointer to extracted item
     */
    item* operator[] (int& index) const;

    // -------------------------------- destructor --------------------------------

    /**
     * Destructor for the catalogue cleaning all the items from catalogue
     */
    ~catalogue();
private:
    vector<item *> _items_vect; /**<_items_vect - vector if items holding items of the catalogue*/
};

/**
 * Class representing continuous items
 */
class continuousItem : public item
{
public:
// -------------------------------- constructor --------------------------------

    /**
     * Constructor for continuous item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     */
    explicit continuousItem(const int& number, string && name, const double& price,
                            const double& quantity) : item(number, move(name), price, quantity)
    {};
};

/**
 * Class representing candy
 */
class candy : public continuousItem
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for candy
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param calories - double value representing calories of the candy
     */
    explicit candy(const int& number, string && name, const double& price,
                   const double& quantity, const double& calories) :
            continuousItem(number, move(name), price, quantity), _calories(calories) {};

    // -------------------------------- methods --------------------------------

    /**
     * Method that prints the candy data
     */
    void print() const override;
private:
    double _calories; /**<_calories - double value representing calories of the candy*/
};

/**
 * Class representing cloth
 */
class cloth : public continuousItem
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for cloth
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param weight - double value representing weight for unit measure of cloth
     */
    explicit cloth(const int& number, string && name, const double& price, const double& quantity,
                   const double& weight) : continuousItem(number, move(name), price, quantity),
                                           _unit_weight(weight) {};

    // -------------------------------- methods --------------------------------

    /**
     * Method that prints the cloth data
     */
    void print() const override;
private:
    double _unit_weight; /**<_unit_weight double representing weight for unit measure of cloth*/
};

/**
 * Class representing item which measured by units
 */
class unitItem : public item
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for unit item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     */
    explicit unitItem(const int& number, string && name, const double& price,
                      const double& quantity) : item(number, move(name), price, quantity) {};
};

/**
 * Class representing media items
 */
class media : public unitItem
{
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for media item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param author - string representing author of the media item
     * @param publ_year - int representing date of publication of media item
     * @param length - int representing length of the media item
     */
    explicit media(const int& number, string && name, const double& price, const double& quantity,
                   string && author, const int& publ_year, const int& length) :
            unitItem(number, move(name), price, quantity), _author(author),
            _publishing_year(publ_year), _length(length) {};

    // -------------------------------- method --------------------------------

    /**
     * Method that prints the media data
     */
    void print() const override;
private:
    string _author; /**<_author string representing author of the media item*/
    int _publishing_year; /**<_publishing_year int representing date of publication of media item*/
    int _length; /**<_length int representing length of the media item*/

};

/**
 * Class representing tool items - items with dimensions that are countable
 */
class tool : public unitItem
{
protected:
    double _dimensions[NUMBER_OF_DIMENSIONS]; /**<_dimensions array representing dimensions of the
 * tool by double values*/
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for tool item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param dims - array representing dimensions of the tool by double values
     */
    explicit tool(const int& number, string && name, const double& price, const double& quantity,
                  const double dims[NUMBER_OF_DIMENSIONS]) : unitItem(number, move(name), price,
                                                                      quantity), _dimensions()
    {
        for(int i = 0; i < NUMBER_OF_DIMENSIONS; ++i)
        {
            _dimensions[i] = dims[i];
        }
    };
};

/**
 * Class representing furniture items - items with dimensions material and color
 */
class furniture : public tool
{
private:
    string _material; /**<_material string representing the material of the furniture item*/
    string _color; /**<_color string representing the color of the furniture item*/
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for furniture item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param dims - array representing dimensions of the tool by double values
     * @param material - string representing the material of the furniture item
     * @param color - string representing the color of the furniture item
     */
    explicit furniture(const int& cat_num, string && cat_name, const double& price,
                       const double& quantity, const double dims[NUMBER_OF_DIMENSIONS],
                       string && material, string && color) : tool(cat_num, move(cat_name), price,
                                                                   quantity, dims),
                                                              _material(material), _color(color){};

    // -------------------------------- methods --------------------------------

    /**
     * Method that prints the furniture data
     */
    void print() const override;
};

/**
 * Class representing crockery items - items with dimensions and capacity
 */
class crockery : public tool
{
private:
    double _capacity; /**<_capacity double representing the capacity of the crockery item*/
public:
    // -------------------------------- constructor --------------------------------

    /**
     * Constructor for crockery item
     * @param number - catalogue number of item
     * @param name - catalogue name of item
     * @param price - double price for unity measure of the item
     * @param quantity - double quantity of the item
     * @param dims - array representing dimensions of the tool by double values
     * @param capacity - double representing the capacity of the crockery item
     */
    explicit crockery(const int& number, string && name, const double& price,
                      const double& quantity, const double dims[NUMBER_OF_DIMENSIONS],
                      const double& capacity) : tool(number, move(name), price, quantity,
                                                     dims), _capacity(capacity) {};

    // -------------------------------- methods --------------------------------

    /**
     * Method that prints the crockery data
     */
    void print() const override;
};

/**
 * Compare two items by its id number (assumption that there are no two items with the same id
 * but different names
 * @param other_it - item to be compared to
 * @return - true if id of the items are equal, false otherwise
 */
bool item::operator== (const item &other_it) const
{
    return (_id == other_it._id);
}

/**
 * The opposite of the operator == :@see operator==
 */
bool item::operator!= (const item &other_it) const
{
    return (_id != other_it._id);
}

catalogue::~catalogue()
{
    for (auto &it : _items_vect)
    {
        delete it;
    }
    _items_vect.clear();
}

/**
 * Method that prints the candy data
 */
void candy::print() const
{
    cout << "Item: " << _id << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << _quantity << endl;
    cout << "Price: " << _price << endl;
    cout << "Calories: " << _calories << endl;
    cout << SEPARATOR_STR << endl;
}

/**
 * Method that prints the cloth data
 */
void cloth::print() const
{
    cout << "Item: " << _id << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << _quantity << endl;
    cout << "Price: " << _price << endl;
    cout << "Weight: " << _unit_weight << endl;
    cout << SEPARATOR_STR << endl;
}

/**
 * Method that prints the furniture data
 */
void furniture::print() const
{
    cout << "Item: " << _id << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << static_cast<int>(_quantity) << endl;
    cout << "Price: " << _price << endl;
    cout << "Dimensions: " << _dimensions[0] << " " << _dimensions[1] << " " << _dimensions[2]
         << endl;
    cout << "Material: " << _material << endl;
    cout << "Color: " << _color << endl;
    cout << SEPARATOR_STR << endl;
}

/**
 * Method that prints the crockery data
 */
void crockery::print() const
{
    cout << "Item: " << _id << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << static_cast<int>(_quantity) << endl;
    cout << "Price: " << _price << endl;
    cout << "Dimensions: " << _dimensions[0] << " " << _dimensions[1] << " " << _dimensions[2]
         << endl;
    cout << "Capacity: " << _capacity << endl;
    cout << SEPARATOR_STR << endl;
}

/**
 * Method that prints the media data
 */
void media::print() const
{
    cout << "Item: " << _id << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << static_cast<int>(_quantity) << endl;
    cout << "Price: " << _price << endl;
    cout << "Author: " << _author << endl;
    cout << "Year of publication: " << _publishing_year << endl;
    cout << "Length: " << _length << endl;
    cout << SEPARATOR_STR << endl;
}

/**
 * Getter of the _id
 * @return - int - representing _id
 */
int item::getCatNumber() const
{
    return _id;
}

/**
 * Getter of the _name
 * @return - to string - representing _name
 */
string item::getCatName() const
{
    return _name;
}

/**
 * Getter of the _quantity
 * @return - double - representing _quantity
 */
double item::getQuantity() const
{
    return _quantity;
}

/**
 * Setter for _quantity
 * @param new_quantity - double - new quantity to be set
 */
void item::setQuantity(double new_quantity)
{
    _quantity = new_quantity;
}

/**
 * Comparison if items based on the id number
 * @param other_it - item to be compared to
 * @return - true if id of 'this' smaller than if of other, false otherwise
 */
bool item::operator< (const item& other_it) const
{
    return (_id < other_it._id);
}

/**
 * Function compares two object of type item by its catalogue numbers
 * @param first_it - left item to be compared
 * @param second_it - right item to be compared
 * @return - true if first less then second, false otherwise
 */
bool compareItemsByNum(item *first_it, item *second_it)
{
    return (*first_it < *second_it);
}

/**
 * Method sorts the catalogue items in accordance to their numbers order
 */
void catalogue::sortCatalogueByNum()
{
    std::sort(_items_vect.begin(), _items_vect.end(), compareItemsByNum);
}

/**
 * Function compares two object of type item by its catalogue names
 * @param first_it - left item to be compared
 * @param second_it - right item to be compared
 * @return - true if first name less then second alphabetically, false otherwise
 */
bool compareItemsByName(item *first_it, item *second_it)
{
    return (first_it->getCatName() == second_it->getCatName()) ? (*first_it < *second_it) :
           (first_it->getCatName() < second_it->getCatName());
}

/**
 * Method sorts the catalogue items in accordance to their names alphabetical order
 */
void catalogue::sortCatalogueByName()
{
    std::sort(_items_vect.begin(), _items_vect.end(), compareItemsByName);
}

/**
 * The [] operator for extracting the item from catalogue place "index"
 * @param index - place of the item to be extracted
 * @return - pointer to extracted item
 */
item* catalogue::operator[] (int& index) const
{
    return _items_vect[index];
}

/**
 * Method adds item to the catalogue, in the case the item already exists in the catalogue,
 * its quantity will be increased, otherwise new item will be created and added
 * @param new_it - item to be added
 * @return - true if trying to add legal item - and it was successfully added, false otherwise
 */
bool catalogue::addItem(item* new_it, int item_cnt)
{
    int index = findByNumber(move(new_it->getCatNumber()));
    if(index != NOT_FOUND_INT)
    {
        if(new_it->getCatName() != (*this)[index]->getCatName())
            // the same numbers but different names
        {
            std::cerr << "product no. " << item_cnt << " already in stock with different type" << endl;
            return false;
        }
        (*this)[index]->setQuantity(new_it->getQuantity() + (*this)[index]->getQuantity());
    }
    else
    {
        _items_vect.push_back(new_it);
    }
    return true;
}

/**
 * Function prints the main menu for choosing the action to be made
 */
void printMenu()
{
    cout << "1. Input stock from file" << endl;
    cout << "2. Find item by catalog number" << endl;
    cout << "3. Find item by name" << endl;
    cout << "4. Print stock by catalog number" << endl;
    cout << "5. Print stock by name" << endl;
    cout << "6. Sell item" << endl;
    cout << "7. Exit" << endl;
}

/**
 * Function gets command from user to do from the main menu
 * @param chosen_cmd - integer representing number of option that user has input
 */
void getCommand(int& chosen_cmd)
{
    while(true)
    {
        printMenu();
        if((cin >> chosen_cmd).good() && chosen_cmd <= 7 && chosen_cmd >= 1)
        {
            break;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR);
    }
}

/**
 * Function cleans all the space beginning from the current position in the file unless other char
 * will be met
 * @param in_file - opened file to clean the spaces in
 */
void cleanSpaces(std::ifstream& in_file)
{
    char c;
    long int beg_pos = in_file.tellg();
    while(in_file.get(c) && (c == SPACE_CHAR))
    {
        ++beg_pos;
    }
    in_file.seekg(beg_pos, in_file.beg);
}

/**
 * Function reads the general parameters for the item from the file
 * @param in_file - input file
 * @param number - catalogue number for the new item
 * @param name - catalogue name for the new item
 * @param price - double - price of the new item
 * @param quantity - double(int) - quantity of the new item
 * @return true if all the data was successfully read, false in any case of invalidity of the file
 */
bool readJointItemParameters(std::ifstream &in_file, int &number, string &name, double &price,
                             double &quantity)
{
    string file_line;
    int feature_index = 0;
    char c;
    while (feature_index < GENERAL_FEATURES_NUM)
    {
        if(!(getline(in_file, file_line, COLON_CHAR)) ||
           (file_line != g_item_features[feature_index]))
        {
            return false;
        }
        switch(feature_index)
        {
            case 0:
                if(!(in_file >> number).good() || (number <= 0) || (!in_file.get(c)) ||
                   (c != NEW_LINE_CHAR))
                {
                    return false;
                }
                break;
            case 1:
                cleanSpaces(in_file);
                if(!(getline(in_file, name)))
                {
                    return false;
                }
                break;
            case 2:
                if(!(in_file >> quantity).good() || (!in_file.get(c)) || (c != NEW_LINE_CHAR))
                {
                    return false;
                }
                break;
            case 3:
                if(!(in_file >> price).good() || (!in_file.get(c)) || (c != NEW_LINE_CHAR))
                {
                    return false;
                }
                break;
            default:
                break;
        }
        ++feature_index;
    }
    return true;
}

/**
 * Function reads the additional parameters for the item from the file
 * @param in_file - input file
 * @param item_type - string representing the type of the item that will be read
 * @param weight - double representing weight for possible cloth
 * @param calories - double representing calories for possible candy
 * @param dimensions - array of three doubles representing dimensions for possible tool
 * @param material - string representing the material for the possible furniture
 * @param color - string representing the color for the possible furniture
 * @param capacity - double representing capacity for the possible crockery
 * @param author - string representing author for the possible media item
 * @param publ_year - int representing publication year for the possible media item
 * @param length - int representing length for the possible media item
 * @return - true if the given item was identified, false in any case of invalidity of the file
 */
bool readAdditionalItemParameters(std::ifstream &in_file, string &item_type, double &weight,
                                  double &calories, double *dimensions, string &material,
                                  string &color, double &capacity, string &author, int &publ_year,
                                  int &length)
{
    string file_line, feature_str;
    vector<string> add_features_vect; // vector - ordered set of given in the file features
    vector<std::streampos> add_features_positions; // places of the values themselves
    while(true) // this loop from set of features between the joint features and separator
    {
        if(!getline(in_file, file_line) && !in_file.eof())
        {
            return false;
        }
        if(file_line == SEPARATOR_STR)
        {
            break;
        }
        feature_str = file_line.substr(0, file_line.find(COLON_CHAR));
        // string representing the part of the whole line that contains feature name
        add_features_positions.emplace_back(static_cast<unsigned long>(in_file.tellg()) -
                                                    (file_line.size() - feature_str.size()));
        // vector holding the positions of the parameters (after the colon sign)
        add_features_vect.push_back(feature_str); // vector holding features in the proper order
    }
    if(add_features_vect == g_candy_add_features)
    {
        in_file.seekg(add_features_positions[0], in_file.beg);
        if(!(in_file >> calories).good())
        {
            return false;
        }
        item_type = CANDY_ITEM_STR;
    }
    else if(add_features_vect == g_cloth_add_features)
    {
        in_file.seekg(add_features_positions[0], in_file.beg);
        if(!(in_file >> weight).good())
        {
            return false;
        }
        item_type = CLOTH_ITEM_STR;
    }
    else if(add_features_vect == g_crockery_add_features)
    {
        in_file.seekg(add_features_positions[0], in_file.beg);
        if(!(in_file >> dimensions[0]).good() || !(in_file >> dimensions[1]).good()
           || !(in_file >> dimensions[2]).good() || !(in_file >> material).good() ||
           !(in_file >> color).good())
        {
            return false;
        }
        in_file.seekg(add_features_positions[1], in_file.beg);
        if(!(in_file >> capacity).good())
        {
            return false;
        }
        item_type = CROCKERY_ITEM_STR;
    }
    else if(add_features_vect == g_furniture_add_features)
    {
        in_file.seekg(add_features_positions[0], in_file.beg);
        if(!(in_file >> dimensions[0]).good() || !(in_file >> dimensions[1]).good()
           || !(in_file >> dimensions[2]).good() || !(in_file >> material).good() ||
           !(in_file >> color).good())
        {
            return false;
        }
        in_file.seekg(add_features_positions[1], in_file.beg);
        cleanSpaces(in_file);
        if(!(in_file >> material).good())
        {
            return false;
        }
        in_file.seekg(add_features_positions[2], in_file.beg);
        cleanSpaces(in_file);
        if(!(in_file >> color).good())
        {
            return false;
        }
        item_type = FURNITURE_ITEM_STR;
    }
    else if(add_features_vect == g_media_add_features)
    {
        in_file.seekg(add_features_positions[0], in_file.beg);
        cleanSpaces(in_file);
        if(!(getline(in_file, author)))
        {
            return false;
        }
        in_file.seekg(add_features_positions[1], in_file.beg);
        if(!(in_file >> publ_year).good())
        {
            return false;
        }
        in_file.seekg(add_features_positions[2], in_file.beg);
        if(!(in_file >> length).good())
        {
            return false;
        }
        item_type = MEDIA_ITEM_STR;
    }
    else // no set of features satisfies the file data
    {
        return false;
    }
    in_file.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR); // pass string with
    in_file.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR); // last feature and
                                                                                // separator string
    return true;
}

/**
 * Function reads the items from the file to the catalogue
 * @param in_file - input file
 * @param stock_catalogue - catalogue where to keep all the items
 * @return - true if all the file is valid and items were red successfully and put to the catalogue
 * false otherwise
 */
bool readItems(std::ifstream& in_file, catalogue& stock_catalogue)
{
    int cat_num, publ_year, length, item_cnt = 1;
    string cat_name, item_type, file_line = SEPARATOR_STR, material, color, author;
    double weight, calories, dimensions[NUMBER_OF_DIMENSIONS], capacity;
    double price, quantity;
    do
    {
        if(!readJointItemParameters(in_file, cat_num, cat_name, price, quantity) ||
           (!readAdditionalItemParameters(in_file, item_type, weight, calories, dimensions,
           material, color, capacity, author, publ_year, length)))
        {
            if(!in_file.eof())
            {
                return false;
            }
        }
        else if(item_type == CANDY_ITEM_STR)
        {
            candy* new_candy;
            new_candy = new(std::nothrow) candy(cat_num, move(cat_name), price, quantity, calories);
            if(!stock_catalogue.addItem(new_candy, item_cnt))
            {
                return false;
            }
        }
        else if(item_type == CLOTH_ITEM_STR)
        {
            cloth* new_cloth;
            new_cloth = new(std::nothrow) cloth(cat_num, move(cat_name), price, quantity, weight);
            if(!stock_catalogue.addItem(new_cloth, item_cnt))
            {
                return false;
            }
        }
        else if(item_type == CROCKERY_ITEM_STR)
        {
            crockery *new_crockery;
            new_crockery = new(std::nothrow) crockery(cat_num, move(cat_name), price, quantity, dimensions,
                                        capacity);
            if (!stock_catalogue.addItem(new_crockery, item_cnt))
            {
                return false;
            }
        }
        else if(item_type == FURNITURE_ITEM_STR)
        {
            furniture* new_furniture;
            new_furniture = new(std::nothrow) furniture(cat_num, move(cat_name), price, quantity, dimensions,
                                          move(material), move(color));
            if(!stock_catalogue.addItem(new_furniture, item_cnt))
            {
                return false;
            }
        }
        else if(item_type == MEDIA_ITEM_STR)
        {
            media* new_media;
            new_media = new(std::nothrow) media(cat_num, move(cat_name), price, quantity, move(author),
                                  publ_year, length);
            if(!stock_catalogue.addItem(new_media, item_cnt))
            {
                return false;
            }
        }
        else // item_type was not initialised
        {
            return false;
        }
        ++item_cnt;
    }while(!in_file.eof());
    return true;
}

/**
 * Function requests for the file path, opens it and read its data to the catalogue
 * @param stock_catalogue - catalogue to keep items from the file
 * in any case of wrong input the function will stop
 */
void readFileToStock(catalogue &stock_catalogue)
{
    string fileAddress;
    cout << "please enter file path: ";
    if(!(cin >> fileAddress).good())
    {
        cout << "Wrong path format" << endl;
        return;
    }
    std::ifstream in_file;
    in_file.open(fileAddress, std::ios::in);
    if(!in_file.is_open())
    {
        std::cerr << "Could not open file." << endl;
        return;
    }
    if(!readItems(in_file, stock_catalogue))
    {
        std::cerr << "File format is invalid" << endl;
        in_file.close();
        return;
    }
    in_file.close();
}

/**
 * Method makes search of the item in the catalogue by given name, and return its index there
 * @param num - catalogue number of the item to be found
 * @return - NOT_FOUND_INT if the item with catalogue number num doen't contained in the
 * catalogue, otherwise index of the found item in the catalogue
 */
int catalogue::findByNumber(int && num) const
{
    int index = 0;
    for(item* cur_it : _items_vect)
    {
        if(cur_it->getCatNumber() == num)
        {
            return index;
        }
        ++index;
    }
    return NOT_FOUND_INT;
}

/**
 * @See findByNumber with find by name instead of number
 * @param name - catalogue name of the item to be found
 */
int catalogue::findByName(const string& name) const
{
    int index = 0;
    for(item* cur_it : _items_vect)
    {
        if(cur_it->getCatName() == name)
        {
            return index;
        }
        ++index;
    }
    return NOT_FOUND_INT;
}

/**
 * Method requests a catalogue number of the item from user, looking for it in the catalogue
 * and then if it was identified prints it to the standard out, else doing nothing
 */
void catalogue::printByInputNumber() const
{
    string input_line;
    cout << "please enter catalog id: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR);
    int input_number;
    getline(cin, input_line);
    std::stringstream ss(input_line);
    if(!(ss >> input_number) || (ss >> input_line))
    {
        std::cerr << endl << "Not valid input" << endl;
        return;
    }
    int item_index = findByNumber(move(input_number));
    if(item_index != NOT_FOUND_INT)
    {
        (*this)[item_index]->print();
    }
    else
    {
        std::cerr << "Item not found" << endl;
    }
}

/**
 * Method requests a catalogue name of the item from user, looking for it in the catalogue
 * and then if it was identified prints it to the standard out, else doing nothing
 */
void catalogue::printByInputName() const
{
    string name;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR);
    cout << "please enter product name: ";
    getline(cin, name, NEW_LINE_CHAR);
    int indexInCat = findByName(name);
    if(indexInCat != NOT_FOUND_INT)
    {
        (*this)[indexInCat]->print();
    }
    else
    {
        std::cerr << "Item not found" << endl;
    }
}

/**
 * Function prints all the catalogue members (items) in the order they are appearing to te
 * current moment in the catalogue
 */
void catalogue::printCatalogueMembers() const
{
    for(item* cur_it_ptr : _items_vect)
    {
        cur_it_ptr->print();
    }
}

/**
 * Method prints all the items from the catalogue in accordance to their numbers order
 */
void catalogue::printByNumber()
{
    sortCatalogueByNum();
    printCatalogueMembers();
}

/**
 * print all the items from the catalogue in accordance to their names alphabetical order
 */
void catalogue::printByName()
{
    sortCatalogueByName();
    printCatalogueMembers();
}

/**
 * Sell 'this' by decreasing its quantity field
 * @param quantity - quantity of units to be sold
 * @return true if item is sold and quantity decreased, false if there is no enough quantity
 */
bool item::sellItem(double& quantity)
{
    if(_quantity < quantity)
    {
        return false;
    }
    else
    {
        setQuantity(_quantity - quantity);
        return true;
    }
}

/**
 * Method request the catalogue number of the item to be sold, and sell it in the case of
 * enough quantity, otherwise doing nothing
 */
void catalogue::sellItem()
{
    int number;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE_CHAR);
    cout << "please enter catalog number: ";
    if(!(cin >> number).good())
    {
        std::cerr << "Wrong format input, please enter the catalogue number" << endl;
        return;
    }
    int indexInCat = findByNumber(move(number)); // index of item in catalogue (-1 if wasn't found)
    if(indexInCat == NOT_FOUND_INT)
    {
        std::cerr << endl << "Product was not found." << endl;
        return;
    }
    double sell_quantity;
    item* found_item = (*this)[indexInCat];
    auto* continuous_item = dynamic_cast<continuousItem*>(found_item); // check if desired item
    // is continuous one or unit item
    continuous_item ? (cout << "Please enter desired quantity: ") :
    (cout << "Please enter number of items: ");
    if(!(cin >> sell_quantity).good() ||
       (!continuous_item && (sell_quantity != int(sell_quantity))))
    {
        std::cerr << "Invalid quantity input" << endl;
        return;
    }
    if(found_item->sellItem(sell_quantity))
    {
        found_item->print();
    }
    else
    {
        std::cerr << endl << "Not enough stock to sell." << endl;
    }
}

/**
 * Realisation of the ikea catalogue, here printing the main menu with options ,and then
 * requesting for commands from the user and making all the activities
 * @return 0 when user chooses the 'exit' option
 */
int main()
{
    int chosen_cmd;
    catalogue stock_catalogue;
    cout.precision(DOUBLE_PRECISION);
    cout << std::fixed;
    while(true)
    {
        getCommand(chosen_cmd);
        switch(chosen_cmd)
        {
            case 1:
                readFileToStock(stock_catalogue);
                break;
            case 2:
                stock_catalogue.printByInputNumber();
                break;
            case 3:
                stock_catalogue.printByInputName();
                break;
            case 4:
                stock_catalogue.printByNumber();
                break;
            case 5:
                stock_catalogue.printByName();
                break;
            case 6:
                stock_catalogue.sellItem();
                break;
            case 7:
                return 0;
            default:
                break;
        }
        cout << endl;
    }
}