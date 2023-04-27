#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	swap(t_env **env, char c)
{
	t_env	*first;
	t_env	*second;

	first = *env;
	second = first->next;
	if (first->next == 0)
		return ;
	first->next = second->next;
	first->previous = second;
	if (second->next != 0)
		second->next->previous = first;
	second->next = first;
	second->previous = NULL;
	*env = second;
	printf("s%c\n", c);
}