# MiniShell Project

## Summary
This project is a journey into building our own simple shell, akin to a minimal bash. 
It's about workings of processes and file descriptors. 

## Features
- A prompt (obviously!)
- Working history
- Quotes (single/doubles)
- Environment variables ($)
- Redirections (<<, >>, <, >)
- Pipes
- $? (last exit status)
- ctrl-C, ctrl-D and ctrl-\
- builtins:
  ◦ echo with option -n
  ◦ cd with only a relative or absolute path
  ◦ pwd with no options
  ◦ export with no options
  ◦ unset with no options
  ◦ env with no options or arguments
  ◦ exit with no options

## Usage
- compile with `make`
- launch with `./minishell`, that's it!

## Requirements
- make
- gcc
