#include "shell.h"

/**
 * _myexit - Exit the shell if requested.
 * @info: Pointer to the struct containing shell information.
 *
 * Return: Returns the exit status or -2 if exit is called.
 */
int _myexit(info_t *info)
{
        int exit_status;

        if (info->argv[1]) /* Check if there is an exit argument */
        {
                exit_status = _erratoi(info->argv[1]);
                if (exit_status == -1)
                {
                        info->status = 2;
                        print_error(info, "Illegal number: ");
                        _eputs(info->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                info->err_num = exit_status;
                return (-2); /* Signal to exit the shell */
        }
        info->err_num = -1;
        return (-2); /* Signal to exit the shell */
}

/**
 * _mycd - Change the current working directory.
 * @info: Pointer to the struct containing shell information.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
        char *current_dir, *new_dir, buffer[1024];
        int chdir_ret;

        current_dir = getcwd(buffer, 1024);
        if (!current_dir)
                _puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                new_dir = _getenv(info, "HOME");
                if (!new_dir)
                        chdir_ret = /* TODO: Handle this case */
                                chdir((new_dir = _getenv(info, "PWD")) ? new_dir : "/");
                else
                        chdir_ret = chdir(new_dir);
        }
        else if (_strcmp(info->argv[1], "-") == 0)
        {
                if (!_getenv(info, "OLDPWD"))
                {
                        _puts(current_dir);
                        _putchar('\n');
                        return (1);
                }
                _puts(_getenv(info, "OLDPWD"));
                _putchar('\n');
                chdir_ret = /* TODO: Handle this case */
                        chdir((new_dir = _getenv(info, "OLDPWD")) ? new_dir : "/");
        }
        else
                chdir_ret = chdir(info->argv[1]);
        if (chdir_ret == -1)
        {
                print_error(info, "can't cd to ");
                _eputs(info->argv[1]);
                _eputchar('\n');
        }
        else
        {
                _setenv(info, "OLDPWD", _getenv(info, "PWD"));
                _setenv(info, "PWD", getcwd(buffer, 1024));
        }
        return (0);
}

/**
 * _myhelp - Display help information.
 * @info: Pointer to the struct containing shell information.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
        char **args;

        args = info->argv;
        _puts("Help command works. Function not yet implemented.\n");
        if (0)
                _puts(*args); /* Temporary workaround to avoid unused variable warning */
        return (0);
}

