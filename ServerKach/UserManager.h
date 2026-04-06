#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>


class UserManager
{
public:
    UserManager();

    //Функция регистрации пользователся
    bool registerUser(const QString &firstName,
                      const QString &lastName,
                      const QString &email,
                      const QString &passwordHash,
                      const QString &gender,
                      const QString &birthDate,
                      double height,
                      double weight,
                      QString &errorMessage,
                      int& userId);

    //Проверка учетных данных
    bool authenticateUser(const QString &email, const QString &password,int& userId);

    //Получение текущего состояния подписки
    int checkSubscriptionStatus(const QString &userId);

    //Загрузка данных из бд
    bool loadUserData(int user_id, QString &first_name, QString &last_name, QString &gender, QString &Age, double &height, double &weight, QString &Goal, int &PlanTrainninnUserData, int &standardSubscription);

    //Обновление данных в БД
    bool updateUserData(int user_id, QString &first_name, QString &last_name,QString &gender, QString &Age, double &height, double &weight, QString &Goal);

    bool saveImage(int user_id, QByteArray &image);

    bool getImage(int user_id, QByteArray &imageData);

    bool saveEPlanTrainningUserData(int user_id, int &EPlanTrainningUser);

    //Замеры
    bool saveUserMeasurements(int &user_id, QString &Data, QString &Weight, QString &Neck_Circumference, QString &Waist_Circumference, QString &Hip_Circumference, QString &Total_Steps_Day);

    bool createMeasurement(int user_id, const QString &date, const QString &weight,
                           const QString &neck, const QString &waist, const QString &hips,
                           const QString &steps, int &measurement_id);

    bool saveMeasurementPhoto(int user_id, int measurement_id, const QString &photoType, const QByteArray &photoData);

    bool getMeasurementPhoto(int measurement_id, const QString &photoType, QByteArray &photoData);

    bool loadUserMeasurements(int user_id, QString &jsonData);

    // ✅ ПРОГРЕСС ПО НЕДЕЛЯМ (блокировка тренировок)
    bool getWorkoutProgress(int user_id, int &current_week,
                            bool &w1_done, bool &w2_done, bool &w3_done,
                            QString &w1_date, QString &w2_date, QString &w3_date,
                            bool &plan_completed);
    bool markWorkoutDone(int user_id, int workout_num, const QString &date);
    void tryAdvanceWeek(int user_id);

    // ✅ Сброс прогресса тренировок
    bool resetWorkoutProgress(int user_id);

    // ✅ Дата начала плана (для системы смены через 2 месяца)
    bool savePlanStartDate(int user_id, const QString &datetime);
    bool getPlanStartDate(int user_id, QString &datetime);
    bool isPlanChangeDue(int user_id, bool &due);

    // ==================== РЕЦЕПТЫ ====================

    // Загрузить все рецепты (возвращает JSON-массив)
    bool loadAllRecipes(QString &jsonData);

    // Загрузить детали одного рецепта (ингредиенты + шаги)
    bool loadRecipeDetails(int recipe_id, QString &jsonData);

    // Добавить новый рецепт (admin)
    bool addRecipe(const QString &name,
                   const QString &mealType,
                   int kcal, int protein, int fat, int carbs,
                   double rating,
                   const QString &ingredient,
                   const QString &img,
                   const QString &ingredientsJson,
                   const QString &stepsJson,
                   int &newId);

    // ==================== ОТЗЫВЫ ====================

    // Сохранить / обновить отзыв пользователя
    bool saveReview(int recipe_id, int user_id, const QString &user_name,
                    int rating, const QString &comment);

    // Загрузить все отзывы рецепта → JSON-массив
    bool loadReviews(int recipe_id, QString &jsonData);

    // Сохранить/обновить рацион на конкретную дату
    bool saveDailyNutrition(int user_id, const QString &date,
                            const QString &mealsJson,
                            int kcal, int protein, int fat, int carbs);

    // Загрузить рацион на конкретную дату
    bool loadDailyNutrition(int user_id, const QString &date,
                            QString &mealsJson,
                            int &kcal, int &protein, int &fat, int &carbs);

    // Загрузить историю всех дней с данными
    bool loadNutritionHistory(int user_id, QString &jsonData);

    // ==================== АДМИН-ПАНЕЛЬ ====================
    bool getAllUsers(QString &jsonData);
    bool setSubscription(int user_id, int status);
    bool deleteRecipe(int recipe_id);
    bool deleteReview(int review_id, int recipe_id);
    bool getUserWorkoutInfo(int user_id, QString &jsonData);
    bool adminResetUserPlan(int user_id);

    // ==================== СТАТИСТИКА ТРЕНИРОВОК ====================
    bool computeAndSaveWeeklyStats(int user_id);
    bool getWorkoutStats(int user_id, QString &jsonData);
    bool clearWorkoutStats(int user_id);

    // ==================== ЗАМЕНЫ УПРАЖНЕНИЙ ====================
    // Сохранить/удалить замену (пустая substituteName = удалить)
    bool saveExerciseSubstitution(int user_id, const QString &originalName, const QString &substituteName);
    // Загрузить все замены пользователя в виде JSON {"оригинал":"замена",...}
    bool loadExerciseSubstitutions(int user_id, QString &jsonData);

    // ==================== ДРУЗЬЯ ====================
    // Получить свой friendId
    bool getUserFriendId(int user_id, int &friendId);
    // Найти пользователя по friendId (исключая себя)
    bool searchUserByFriendId(int myUserId, int targetFriendId, QString &jsonData);
    // Отправить запрос в друзья (by friendId target); toUserId — получатель (для push-уведомления)
    bool sendFriendRequest(int fromUserId, int targetFriendId, QString &errorMessage, int &toUserId);
    // Получить входящие запросы в друзья (status='pending', to_user_id=myId)
    bool getIncomingFriendRequests(int userId, QString &jsonData);
    // Принять запрос
    bool acceptFriendRequest(int myUserId, int requestId);
    // Отклонить запрос
    bool declineFriendRequest(int myUserId, int requestId);
    // Получить список друзей с именем, возрастом, целью, аватаром
    bool getFriends(int userId, QString &jsonData);
    // Удалить друга
    bool removeFriend(int myUserId, int friendUserId);


    // ✅ SAVE TRAINING - Все 19 тренировок
    bool saveTrainingButtockBridgeP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingChestPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingHorizontalThrustP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingOneLegBenchPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingPressOnMatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingVerticalThrustP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingPressOnBallP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingKettlebellSquatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingRomanianDeadliftP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingKneePushupP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingHipAbductionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingTricepExtensionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingAssistedPullupP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingBulgarianSplitSquatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingShoulderPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingCableFlyP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingLegExtensionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingPlankP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool saveTrainingChestFlyP1(int user_id,float &approach1, float &approach2, float &approach3);

    // ✅ GET TRAINING - Все 19 тренировок
    bool GetSaveTrainingButtockBridgeP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingChestPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingHorizontalThrustP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingOneLegBenchPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingPressOnMatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingVerticalThrustP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingPressOnBallP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingKettlebellSquatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingRomanianDeadliftP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingKneePushupP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingHipAbductionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingTricepExtensionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingAssistedPullupP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingBulgarianSplitSquatP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingShoulderPressP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingCableFlyP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingLegExtensionP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingPlankP1(int user_id,float &approach1, float &approach2, float &approach3);
    bool GetSaveTrainingChestFlyP1(int user_id,float &approach1, float &approach2, float &approach3);

private:
    //Объект базы данных
    QSqlDatabase db;

    struct User {
        QString firstName;
        QString lastName;
        QString email;
        QString passwordHash;
        QString gender;
        QDate birthDate;
        double height;
        double weight;
    };

    //Объект данных пользователя
    User userData;

    //Метод для хэширования пароля
    void hashPassword(QString &password);

    // Инициализация таблиц БД
    void initializeTables();

    // Начальные данные рецептов (вызывается один раз, если таблица пустая)
    void seedInitialRecipes();
};

#endif // USERMANAGER_H
