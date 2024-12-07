# Task Tracker

This project is used to track and manage tasks from a command line interface.\
[Link](https://roadmap.sh/projects/task-tracker) to the project page.

Here are sample use cases of the program:
<pre>
$ ./task-tracker 
Usage:
  add [description]          - Add a new task
  update [id] [description]  - Update a task description
  delete [id]                - Delete a task
  mark-done [id]             - Mark a task as done
  mark-in-progress [id]      - Mark a task as in-progress
  list                       - List all tasks
  list [status]              - List tasks by status (done[0], in-progress[1], todo[2])

$ ./task-tracker add "Buy groceries"
New task with id #0 added to tasks list.

$ ./task-tracker list
ID   Description                                       Status      Created At          Modified At         
0    Buy groceries                                     2           2024-12-07 23:03:10 2024-12-07 23:03:10 
1    Finish project                                    2           2024-12-07 23:04:16 2024-12-07 23:04:16 
2    Fix bird house                                    2           2024-12-07 23:05:24 2024-12-07 23:05:24

$ ./task-tracker update 1 "Finish task-cli project"
Successfully changed description of task #1.

$ ./task-tracker mark-done 2

$ ./task-tracker list
ID   Description                                       Status      Created At          Modified At         
0    Buy groceries                                     2           2024-12-07 23:03:10 2024-12-07 23:03:10 
1    Finish task-cli project                           2           2024-12-07 23:04:16 2024-12-07 23:07:14 
2    Fix bird house                                    0           2024-12-07 23:05:24 2024-12-07 23:07:41
<pre>

