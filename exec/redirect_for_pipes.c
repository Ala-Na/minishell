int		check_redirections(t_infos *infos, t_cmd *cmd)
{
	if (!infos || !cmd)
		return (return_error(1, "something went wrong", 0, -1));
	while (cmd->next_operator != PIPE || cmd->next_operator != -1)
	{
		if (cmd->next_operator == LT && cmd->next)
			return (do_lesser_redirect(infos, cmd));
		else if (cmd->next_operator == LT_DBL && cmd->next)
			return (do_double_lesser_redirect(infos, cmd));
		else if (cmd->next_operator == GT && cmd->next)
			return (do_greater_redirect(infos, cmd));
		else if (cmd->next_operator == GT_DBL && cmd->next)
			return (do_greater_double_redirect(infos, cmd));
		else
			return (return_error(1, "something went wrong", 0, -1));
		cmd->next_operator = cmd->next->next_operator;
		cmd->end->next = cmd->next->start->next;
		cmd->end = cmd->next->end;
		cmd->next = cmd->next->next;
	}
	return (0);
}
