#include <microhttpd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // for sleep()

#define PORT 8080

static enum MHD_Result request_handler(void *cls,
                                       struct MHD_Connection *connection,
                                       const char *url,
                                       const char *method,
                                       const char *version,
                                       const char *upload_data,
                                       size_t *upload_data_size,
                                       void **con_cls)
{
    const char *response_str;

    if (strcmp(method, "GET") == 0) {
        response_str = "GET";
    } else if (strcmp(method, "POST") == 0) {
        response_str = "POST";
    } else if (strcmp(method, "PUT") == 0) {
        response_str = "PUT";
    } else if (strcmp(method, "DELETE") == 0) {
        response_str = "DELETE";
    } else {
        response_str = "OTHER";
    }

    struct MHD_Response *response;
    enum MHD_Result ret;

    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void *)response_str,
                                               MHD_RESPMEM_PERSISTENT);

    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD,
                              PORT,
                              NULL, NULL,
                              &request_handler, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon)
    {
        fprintf(stderr, "Failed to start server\n");
        return 1;
    }

    printf("Server running on http://0.0.0.0:%d\n", PORT);

    // Keep process alive
    while (1) {
        sleep(60);
    }

    MHD_stop_daemon(daemon);
    return 0;
}
