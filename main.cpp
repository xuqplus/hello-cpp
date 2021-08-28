#include <iostream>
#include <config.h>
#include <curl/curl.h>

using namespace std;

void config_print()
{
    std::cout << "HELLO_CPP_VERSION_MAJOR -> " << HELLO_CPP_VERSION_MAJOR << std::endl;
    std::cout << "HELLO_CPP_VERSION_MINOR -> " << HELLO_CPP_VERSION_MINOR << std::endl;
}

#include <my-lib.h>
void run_function_in_my_lib()
{
    function_in_my_lib();
}

void test_curl()
{
    CURL *curl;
    CURLcode res;
    // curl_global_init(CURL_GLOBAL_DEFAULT);
    // curl = curl_easy_init();
    // if (curl)
    // {
    //     curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/");
    //     res = curl_easy_perform(curl);
    //     /* Check for errors */
    //     if (res != CURLE_OK)
    //         fprintf(stderr, "curl_easy_perform() failed: %s\n",
    //                 curl_easy_strerror(res));
    //     /* always cleanup */
    //     curl_easy_cleanup(curl);
    // }
    // curl_global_cleanup();
}

int main(int, char **)
{
    std::cout << "hello cpp .." << std::endl;

    config_print();

    run_function_in_my_lib();

    test_curl();
    return 0;
}
