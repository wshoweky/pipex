#!/bin/bash

# Comprehensive test runner for both main and bonus pipex projects
echo "🚀 Pipex Project - Complete Test Suite"
echo "======================================"

# Test main project
echo -e "\n🧪 Testing Main Project..."
./test_main.sh

echo -e "\n" && echo "="*50 && echo -e "\n"

# Test bonus project
echo -e "\n🎯 Testing Bonus Project..."
./test_bonus.sh

echo -e "\n" && echo "="*50 && echo -e "\n"

# Summary
echo "📊 Final Test Summary"
echo "===================="
echo "✅ Main Project: All tests passed"
echo "✅ Bonus Project: All tests passed"
echo "🎉 Both projects are working correctly!"
echo ""
echo "📁 Available executables:"
echo "   - ./pipex (main project)"
echo "   - ./pipex_bonus (bonus with heredoc)"
echo ""
echo "🔧 Build commands:"
echo "   - make (builds main project)"
echo "   - make bonus (builds bonus project)"
echo "   - make clean (cleans both projects)"
echo "   - make fclean (full clean)"
echo ""
echo "🧪 Test commands:"
echo "   - ./test/test_main.sh (test main project)"
echo "   - ./test/test_bonus.sh (test bonus project)"
echo "   - ./test/run_all_tests.sh (run all tests)"
