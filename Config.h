#ifndef CONFIG_H
#define CONFIG_H

#define FILM_OWNER_SHARE_HIGHLY_RATED 0.95
#define FILM_OWNER_SHARE_AVERAGE_RATED 0.9
#define FILM_OWNER_SHARE_LOW_RATED 0.8
#define HIGH_RATED 3
#define LOW_RATED 1
#define AVERAGE_RATED 2

#define IS_PUBLISHER "true"
#define IS_NOT_PUBLISHER "false"
#define MAX_POINT 10
#define MAX_KEYS_AND_VALUES_FOR_SIGNUP 10
#define MIN_KEYS_AND_VALUES_FOR_SIGNUP 8
#define MIN_KEYS_AND_VALUES_FOR_LOGIN 4
#define MAX_KEYS_AND_VALUES_FOR_LOGIN 4
#define MAX_KEYS_AND_VALUES_FOR_FILM_UPLOAD 12
#define MIN_KEYS_AND_VALUES_FOR_FILM_UPLOAD 12
#define MAX_KEYS_AND_VALUES_FOR_FILM_EDIT 12
#define MIN_KEYS_AND_VALUES_FOR_FILM_EDIT 2
#define MAX_KEYS_AND_VALUES_FOR_FILM_DELETE 2
#define MIN_KEYS_AND_VALUES_FOR_FILM_DELETE 2
#define MIN_KEYS_AND_VALUES_FOR_FILM_SEARCH 0 
#define MAX_KEYS_AND_VALUES_FOR_FILM_SEARCH 12
#define MIN_KEYS_AND_VALUES_FOR_FOLLOW 2 
#define MAX_KEYS_AND_VALUES_FOR_FOLLOW 2
#define MIN_KEYS_AND_VALUES_FOR_ADD_CREDIT 2
#define MAX_KEYS_AND_VALUES_FOR_ADD_CREDIT 2
#define DL_KW "DELETE"
#define GET_KW "GET"
#define POST_KW "POST"
#define PUT_KW "PUT"
#define COMMAND_END_SIGN "?"
#define COMMAND_DELIMITER ' '
#define BASIC_ID_VALUE 1
#define REGISTER_C0MMAND "signup"
#define LOGIN_COMMAND "login"
#define FILMS_COMMAND "films"
#define FOLLOWERS_COMMAND "followers"
#define GET_MONEY_COMMAND "money"
#define GET_PUBLISHED_FILMS_COMMAND "published"
#define REPLY_COMMAND "replies"
#define COMMENTS_COMMAND "comments"
#define BUY_COMMAND "buy"
#define RATE_COMMAND "rate"
#define PURCHASES_COMMAND "purchased"
#define NOTIFICATIONS_COMMAND "notifications"
#define READ_NOTIFICATIONS_COMMAND "notificationsread"
#define EMAIL_KEY "email" 
#define USERNAME_KEY "username"
#define PASSWORD_KEY "password"
#define AGE_KEY "age"
#define PUBLISHER_KEY "publisher"
#define FILM_NAME_KEY "name"
#define FILM_YEAR_KEY "year"
#define FILM_LENGTH_KEY "length"
#define FILM_PRICE_KEY "price"
#define FILM_SUMMARY_KEY "summary"
#define FILM_DIRECTOR_KEY "director"
#define FILM_ID_KEY "film_id"
#define FILM_MINIMUM_RATE_KEY "min_rate"
#define FILM_MINIMUM_YEAR_KEY "min_year"
#define FILM_MAXIMUM_YEAR_KEY "max_year"
#define COMMENT_ID_KEY "comment_id"
#define COMMENT_CONTENT_KEY "content"
#define USER_ID_KEY "user_id"
#define MONEY_AMOUNT_KEY "amount"
#define SCORE_GIVEN_KEY "score"
#define LIMIT_COMMENTS_SHOWN_KEY "limit"
#define SUCCESS_MESSAGE "OK"

#endif