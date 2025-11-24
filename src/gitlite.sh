#!/bin/bash

# GitLite Advanced CLI with OS-level features
# Support for process management and IPC

EXECUTABLE="./build/gitlite"

if [ ! -f "$EXECUTABLE" ]; then
    echo "❌ Executable not found. Run: make"
    exit 1
fi

case $1 in
  init)
    $EXECUTABLE init
    ;;
  add)
    $EXECUTABLE add "$2"
    ;;
  commit)
    $EXECUTABLE commit "$2"
    ;;
  log)
    $EXECUTABLE log
    ;;
  status)
    $EXECUTABLE status
    ;;
  diff)
    $EXECUTABLE diff "$2"
    ;;
  restore)
    $EXECUTABLE restore "$2"
    ;;
  branch)
    $EXECUTABLE branch "$2"
    ;;
  merge)
    $EXECUTABLE merge "$2"
    ;;
  parallel-add)
    # Uses multi-threading for bulk operations
    $EXECUTABLE parallel-add "$2"
    ;;
  *)
    echo "📘 GitLite Commands:"
    echo "  ./gitlite.sh init"
    echo "  ./gitlite.sh add <file>"
    echo "  ./gitlite.sh commit \"message\""
    echo "  ./gitlite.sh log"
    echo "  ./gitlite.sh status"
    echo "  ./gitlite.sh diff <file>"
    echo "  ./gitlite.sh restore <file>"
    echo "  ./gitlite.sh branch <name>"
    echo "  ./gitlite.sh merge <branch>"
    echo "  ./gitlite.sh parallel-add <directory>"
    ;;
esac
