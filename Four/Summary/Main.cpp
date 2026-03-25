#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe() = default;

    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

void printRecipe(const PotionRecipe& recipe, int index = -1) {
    if (index != -1) {
        std::cout << index << ". ";
    }

    std::cout << "물약 이름: " << recipe.potionName << std::endl;
    std::cout << "   >> 필요 재료: ";

    for (size_t i = 0; i < recipe.ingredients.size(); ++i) {
        std::cout << recipe.ingredients[i];
        if (i + 1 < recipe.ingredients.size()) {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;
}

class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
     
        for (const auto& recipe : recipes) {
            if (recipe.potionName == name) {
                std::cout << ">> 같은 이름의 물약은 등록할 수 없습니다." << std::endl;
                return;
            }
        }

        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다!" << std::endl;
    }

    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            printRecipe(recipes[i], static_cast<int>(i + 1));
        }
        std::cout << "-----------------------------\n";
    }


    PotionRecipe searchRecipeByName(const std::string& name) const {
        for (const auto& recipe : recipes) {
            if (recipe.potionName == name) {
                return recipe;
            }
        }
        return PotionRecipe();
    }

    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient) const {
        std::vector<PotionRecipe> results;

        for (const auto& recipe : recipes) {
            if (std::find(recipe.ingredients.begin(), recipe.ingredients.end(), ingredient)
                != recipe.ingredients.end()) {
                results.push_back(recipe);
            }
        }

        return results;
    }
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "\n🧪 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료로 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << ">> 물약 이름이 비어 있어 레시피 추가를 취소합니다." << std::endl;
                continue;
            }

            std::vector<std::string> ingredientsInput;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)\n";

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                if (ingredient == "끝") {
                    break;
                }         

                ingredientsInput.push_back(ingredient);
            }

            if (!ingredientsInput.empty()) {
                myWorkshop.addRecipe(name, ingredientsInput);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }
        }
   

        else if (choice == 2) {
            myWorkshop.displayAllRecipes();
        }
        else if (choice == 3) {
            std::string name;
            std::cout << "검색할 물약 이름: ";
            std::getline(std::cin, name);

            PotionRecipe result = myWorkshop.searchRecipeByName(name);

            if (result.potionName.empty()) {
                std::cout << ">> '" << name << "' 레시피를 찾을 수 없습니다." << std::endl;
            }
            else {
                std::cout << "\n[ 물약 이름 검색 결과 ]" << std::endl;
                printRecipe(result, 1);
                std::cout << "------------------------------\n";
            }
        }
        else if (choice == 4) {
            std::string ingredient;
            std::cout << "검색할 재료 이름: ";
            std::getline(std::cin, ingredient);

            std::vector<PotionRecipe> results = myWorkshop.searchRecipeByIngredient(ingredient);

            if (results.empty()) {
                std::cout << ">> '" << ingredient << "' 재료가 포함된 레시피를 찾을 수 없습니다." << std::endl;
            }
            else {
                std::cout << "\n[ 재료 검색 결과]" << std::endl;
                for (size_t i = 0; i < results.size(); ++i) {
                    printRecipe(results[i], static_cast<int>(i + 1));
                }
                std::cout << "-------------------------\n";
            }
        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 선택입니다. 다시 선택하세요." << std::endl;
        }
    }

    return 0;
}