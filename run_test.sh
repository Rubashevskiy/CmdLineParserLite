#!/bin/bash

#Название проекта
project="cmdlineparserlite"
#Каталог проекта
path=$PWD
#Каталог сборки
build="build"
#Аргументы для передачи тестовому приложению
arg_1="SELECT command_select -ht test_string"
arg_2="UPDATE command_update --help -t test_string"

function dialogYNX () {
  if ([ ! -n "$1" ]); then 
    echo "Error dialogYNX: param is empty"
    exit 1
  fi
  while [ 1 = 1 ]; 
  do
    read -p "$1 (y - Yes, n - No x - Exit) " -n 1 -r
    if [[ $REPLY =~ ^[Yy]$ ]]; then
      echo
      return 0
    fi
    if [[ $REPLY =~ ^[Nn]$ ]]; then
      echo
      return 1
    fi
    if [[ $REPLY =~ ^[Xx]$ ]]; then
      echo "Exit"
      exit
    fi
    echo
  done
}

#Проверка наличия приложения.
#Аргументы: Имя приложения.
#Возвращает 0 - Есть || 1 - Нет
function isApp () {
  if ( ! [ -n "$1" ]); then
    echo "Error isApp: param is empty"
    exit 1
  fi
  if ([ -x "$(command -v $1)" ]); then
    return 0
  else
    return 1
  fi
}



# Проверка существования тестового приложения в каталоге build
if (! isApp "${path}/${build}/${project}"); then
  echo "ERROR: Test App ${path}/${build}/${project} not find!!!"
  exit
fi

if (dialogYNX "Run test project?"); then
  echo "RUN test 1. Arg  ${arg_1}"
  if (${path}/${build}/${project} ${arg_1}); then
    echo "Test App OK"
  else 
    echo "Test App error"
  fi
  echo "RUN test 2. Arg  ${arg_2}"
  if (${path}/${build}/${project} ${arg_2}); then
    echo "Test App OK"
  else 
    echo "Test App error"
  fi
fi















