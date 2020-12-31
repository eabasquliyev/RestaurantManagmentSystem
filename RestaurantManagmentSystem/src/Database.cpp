#include "Database.h"
#include "DatabaseHelper.h"
#include "Exception.h"

void Database::addAdmin(const std::string& username, const std::string& password)
{
	admins.push_back(Admin(username, std::to_string(DatabaseHelper::generateHash(password))));
}
void Database::deleteAdmin(const std::string& username) {
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		if (username == i->getUsername())
			admins.remove(*i); return;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no admins associated this username -> " + username));
}
void Database::updateAdmin(const std::string& username, std::shared_ptr<Admin> new_admin)
{
	bool flag = false;
	size_t admin_id;
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		if (username == i->getUsername())
		{
			admin_id = i->getID();
			admins.remove(*i);
			flag = true;
			break;
		}
	}
	
	if (flag)
	{
		new_admin->setID(admin_id);
		admins.push_back(*new_admin);
	}
	else
	{
		throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no admins associated this username -> " + username));
	}


}
void Database::showAllAdmins() const
{
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		std::cout << *i << std::endl;
	}
}

void Database::addOrder(const std::shared_ptr<Table>& table, const std::shared_ptr<Meal>& meal, const size_t& amount)
{
	std::shared_ptr<Order> order_ptr(new Order(table->getTableNo(), meal, amount));
	orders.push_back(order_ptr); // add to all order list
	table->addOrder(order_ptr); // add to table order list
}
void Database::deleteOrder(const std::shared_ptr<Order>& order)
{
	this->orders.remove(order);

	for (auto& i : this->tables)
	{
		if (order->getTableNo() == i->getTableNo())
		{
			i->deleteOrder(order);
		}
	}
}
void Database::deleteAllOrders()
{
	this->orders.clear();
}

void Database::showAllOrder(const bool &shortInfo)
{
	if (shortInfo)
	{
		for (auto i = orders.begin(); i != orders.end(); i++)
		{
			std::cout << *(*i) << std::endl;
		}
	}
	else
	{
		for (auto i = orders.begin(); i != orders.end(); i++)
		{
			(*i)->fullInfo();
		}
	}
}
void Database::showOrdersByTable(const std::string& table_no, const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (table_no == (*i)->getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					std::cout << *(*j) << std::endl;
				}
				return;
			}
		}
	}
	else
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (table_no == (*i)->getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					(*j)->fullInfo();
				}
				return;
			}
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + table_no));
}
void Database::showOrdersByTable(const size_t& id, const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (id == (*i)->getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					std::cout << *(*j) << std::endl;
				}
				return;
			}
		}
	}
	else
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (id == (*i)->getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					(*j)->fullInfo();
				}
				return;
			}
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table id -> " + id));
}
std::shared_ptr<Order>& Database::getOrder(const size_t& id)
{
	for (auto& i : this->orders)
	{
		if (id == i->getID())
			return i;
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no order associated this id ->" + std::to_string(id)));
}

std::shared_ptr<Table> Database::addTable(const std::string& table_no) {
	std::shared_ptr<Table> table(new Table(table_no));
	tables.push_back(table);
	return table;
}
std::shared_ptr<Table> Database::getTableByNo(const std::string& table_no)
{
	for (auto& i : this->tables)
	{
		if (table_no == i->getTableNo())
			return i;
	}

	std::shared_ptr<Table> null;// (new Table("null"));  Table::current_id--;
	return null;
}
void Database::deleteTable(const std::string& table_no) {
	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (table_no == (*i)->getTableNo())
		{
			tables.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + table_no));
}
void Database::deleteTable(const size_t& id)
{
	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (id == (*i)->getID())
		{
			tables.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + std::to_string(id)));
}

void Database::addMeal(const std::shared_ptr<Meal>& meal) {
	this->meals.push_back(meal);
}
void Database::deleteMeal(const size_t& id){
	for (auto& meal : this->meals)
	{
		if (id == meal->getID())
		{
			meals.remove(meal);
			return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this ->" + std::to_string(id)));
}
void Database::deleteAllMeal()
{
	this->meals.clear();
}
void Database::updateMeal(std::shared_ptr<Meal> &old_meal, const std::shared_ptr<Meal>& new_meal){
	old_meal->setName(new_meal->getName());
	old_meal->setCategory(new_meal->getCategory());
	old_meal->setMenuRating(new_meal->getMenuRating());

	Meal::current_id--;
}
void Database::deleteIngredientFromMeal(std::shared_ptr<Meal>& meal, const size_t& ingredient_id, const size_t& amount){
	std::list<std::shared_ptr<RecipeItem>> ingredient_items = meal->getIngredientItems();
	for (auto& ingredient_item : ingredient_items)
	{
		if (ingredient_id == ingredient_item->getIngredient()->getID())
		{
			if (amount == 0)
			{
				meal->deleteIngredientByID(ingredient_id);
			}
			else
			{
				meal->decreaseAmountOfIngredient(ingredient_item, amount);
			}
			return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id ->" + std::to_string(ingredient_id)));
}
void Database::addIngredientToMeal(std::shared_ptr<Meal>& meal, std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	std::list<std::shared_ptr<RecipeItem>> ingredient_items = meal->getIngredientItems();

	for (auto& i : ingredient_items)
	{
		if (ingredient->getID() == i->getIngredient()->getID())
		{
			i->setAmount(i->getAmount() + amount);
			return;
		}
	}

	// eger meal icherisinde hemin ingredient olmasa yenisi elave olunur

	meal->addIngredient(ingredient, amount);
}
std::shared_ptr<Meal>& Database::getMeal(const size_t& id){
	for (auto& i : this->meals)
	{
		if (id == i->getID())
			return i;
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this id ->" + std::to_string(id)));
}
void Database::showAllMeal(const bool& shortInfo) const
{
	if (shortInfo)
	{
		for (auto& meal : this->meals)
		{
			meal->showShortInfo();
		}
	}
	else
	{
		for (auto& meal : this->meals)
		{
			meal->showFullInfo();
		}
	}
	std::cout << std::string(37, '#') << std::endl;
}
size_t Database::getMealCount() const { return this->meals.size(); }
void Database::filterMeals(const std::string& mealName)
{
	std::string tmpName = DatabaseHelper::stringToLower(mealName);
	bool founded = false;
	for (auto& meal : this->meals)
	{
		std::string tmp = DatabaseHelper::stringToLower(meal->getName());
		size_t str_pos = tmp.find(tmpName);
		if (tmp.size() >= str_pos)
		{
			meal->showFullInfo();
			founded = true;
		}
	}

	if (!founded)
		throw ClientException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this meal -> " + mealName));

	std::cout << std::string(37, '#') << std::endl;
}