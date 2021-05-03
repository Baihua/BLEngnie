

workspace "BigLine"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "BL"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include("glad");
include("BL")