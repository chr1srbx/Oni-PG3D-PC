#pragma once
#include <corecrt_math_defines.h>
#include "../imgui/imgui_internal.h"

#include <cmath>
#include <cstdlib>


void DrawCorner(ImVec2 start, ImVec2 end, ImVec4 color, int thickness, ImDrawList* background) {
    background->AddLine(start, end, ImColor(color), thickness);
}

void DrawBox22(float x, float y, float width, float height, ImVec4 color, int thickness, ImDrawList* background) {
    ImVec2 topLeft(x, y);
    ImVec2 topRight(x + width, y);
    ImVec2 bottomRight(x + width, y + height);
    ImVec2 bottomLeft(x, y + height);

    float cornerLength = fmin(width, height) * 0.1f;  // Dynamic length of the corner lines (10% of the smallest dimension)

    // Draw filled background
    background->AddRectFilled(topLeft, bottomRight, ImColor(color), 0.0f);

    // Top-left corner
    DrawCorner(topLeft, ImVec2(topLeft.x + cornerLength, topLeft.y), color, thickness, background);
    DrawCorner(topLeft, ImVec2(topLeft.x, topLeft.y + cornerLength), color, thickness, background);

    // Top-right corner
    DrawCorner(topRight, ImVec2(topRight.x - cornerLength, topRight.y), color, thickness, background);
    DrawCorner(topRight, ImVec2(topRight.x, topRight.y + cornerLength), color, thickness, background);

    // Bottom-right corner
    DrawCorner(bottomRight, ImVec2(bottomRight.x - cornerLength, bottomRight.y), color, thickness, background);
    DrawCorner(bottomRight, ImVec2(bottomRight.x, bottomRight.y - cornerLength), color, thickness, background);

    // Bottom-left corner
    DrawCorner(bottomLeft, ImVec2(bottomLeft.x + cornerLength, bottomLeft.y), color, thickness, background);
    DrawCorner(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - cornerLength), color, thickness, background);
}

void DrawEdgeFilled(float x, float y, float width, float height, ImVec4 color, ImDrawList* background) {
    DrawBox22(x + 3 - 1, y + 3 - 1, width - 5 * 2 + 2, height - 3 * 2 + 2, ImColor(110, 94, 81), 2, background);
}



// Function to draw a 3D ESP box
/*void DrawWEspBox33D(Vec3 top, Vec3 bot, float a, int width, int thickness, ImVec4 color, ImDrawList* background) {
    int height3D = std::abs(top.z - bot.z);
    Vec3 b1, b2, b3, b4, t1, t2, t3, t4;

    b1.z = b2.z = b3.z = b4.z = bot.z;

    float angleOffset = M_PI / 4;

    b1.x = bot.x + std::cos(a + angleOffset) * width;
    b1.y = bot.y + std::sin(a + angleOffset) * width;

    b2.x = bot.x + std::cos(a + 3 * angleOffset) * width;
    b2.y = bot.y + std::sin(a + 3 * angleOffset) * width;

    b3.x = bot.x + std::cos(a + 5 * angleOffset) * width;
    b3.y = bot.y + std::sin(a + 5 * angleOffset) * width;

    b4.x = bot.x + std::cos(a + 7 * angleOffset) * width;
    b4.y = bot.y + std::sin(a + 7 * angleOffset) * width;

    t1 = { b1.x, b1.y, b1.z + height3D };
    t2 = { b2.x, b2.y, b2.z + height3D };
    t3 = { b3.x, b3.y, b3.z + height3D };
    t4 = { b4.x, b4.y, b4.z + height3D };

    // Convert 3D coordinates to 2D (using some projective transform function)
    auto ProjectTo2D = [](const Vec3& vec) -> ImVec2 {
        // Placeholder for actual 3D to 2D projection
        return ImVec2(vec.x, vec.y);
        };

    ImVec2 b1_2 = ProjectTo2D(b1);
    ImVec2 b2_2 = ProjectTo2D(b2);
    ImVec2 b3_2 = ProjectTo2D(b3);
    ImVec2 b4_2 = ProjectTo2D(b4);
    ImVec2 t1_2 = ProjectTo2D(t1);
    ImVec2 t2_2 = ProjectTo2D(t2);
    ImVec2 t3_2 = ProjectTo2D(t3);
    ImVec2 t4_2 = ProjectTo2D(t4);

    // Draw lines with the color and background draw list
    auto DrawLine = [&](ImVec2 p1, ImVec2 p2, ImVec4 color, ImDrawList* background) {
        background->AddLine(p1, p2, ImColor(color), thickness);
        };

    // Draw the edges
    DrawLine(t1_2, b1_2, color, background);
    DrawLine(t2_2, b2_2, color, background);
    DrawLine(t3_2, b3_2, color, background);
    DrawLine(t4_2, b4_2, color, background);

    // Draw the top base
    DrawLine(t1_2, t2_2, color, background);
    DrawLine(t2_2, t3_2, color, background);
    DrawLine(t3_2, t4_2, color, background);
    DrawLine(t4_2, t1_2, color, background);

    // Draw the bottom base
    DrawLine(b1_2, b2_2, color, background);
    DrawLine(b2_2, b3_2, color, background);
    DrawLine(b3_2, b4_2, color, background);
    DrawLine(b4_2, b1_2, color, background);
}*/


// Define a simple Vec3 structure
struct Vec3 {
    float x, y, z;
};




// Function to draw a flat 3D circle by applying perspective distortion
void DrawCircle3D(ImDrawList* draw_list, ImVec2 center, float radius, ImVec4 color, int num_segments = 100, float perspective = 0.5f)
{
    if (num_segments <= 0) num_segments = 100;

    const float angle_increment = 2.0f * 3.14159265359f / num_segments;
    const ImU32 col = IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255);

    ImVec2* points = new ImVec2[num_segments];
    for (int i = 0; i < num_segments; ++i)
    {
        float angle = i * angle_increment;
        // Apply perspective distortion to the Y axis
        points[i] = ImVec2(center.x + cosf(angle) * radius, center.y + sinf(angle) * radius * perspective);
    }

    draw_list->AddPolyline(points, num_segments, col, true, 1.0f);

    delete[] points;
}

void DrawLine(ImVec2 start, ImVec2 end, ImVec4 color, ImDrawList* background) {
    if (background) {
        background->AddLine(start, end, ImColor(color.x, color.y, color.z, color.w), 1);
    }
}

void DrawBox(ImVec4 rect, ImVec4 color, int thickness, ImDrawList* background) {
    ImVec2 v1(rect.x, rect.y);
    ImVec2 v2(rect.x + rect.z, rect.y);
    ImVec2 v3(rect.x + rect.z, rect.y + rect.w);
    ImVec2 v4(rect.x, rect.y + rect.w);

    DrawLine(v1, v2, color, background);
    DrawLine(v2, v3, color, background);
    DrawLine(v3, v4, color, background);
    DrawLine(v4, v1, color, background);
}

void DrawBox2(float x, float y, float width, float height, ImColor color, int thickness, ImDrawList* background)
{
    if (background) {
        background->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color, 0, thickness);
    }
}

void DrawOutlinedBox2(float x, float y, float width, float height, ImVec4 color, ImDrawList* background)
{
    DrawBox2(x + 3 - 1, y + 3 - 1, width - 5 * 2 + 2, height - 3 * 2 + 2, ImVec4(color), 1, background);
}



// Function to project 3D coordinates to 2D screen space
// This is a placeholder and should be replaced with actual 3D projection code
ImVec2 Project3DTo2D(Vec3 pos)
{
    // Assuming a simple orthographic projection for this example
    // You should replace this with your actual 3D to 2D projection logic
    return ImVec2(pos.x, pos.y);
}

// Function to draw a 3D box with outlined edges
void DrawOutlinedBox3(float x, float y, float z, float width, float height, float depth, ImVec4 color, ImDrawList* background)
{
    // Define the eight vertices of the 3D box
    Vec3 vertices[8] = {
        {x, y, z},
        {x + width, y, z},
        {x + width, y + height, z},
        {x, y + height, z},
        {x, y, z + depth},
        {x + width, y, z + depth},
        {x + width, y + height, z + depth},
        {x, y + height, z + depth}
    };

    // Define the indices for the edges of the box
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Draw the edges of the box
    for (int i = 0; i < 12; ++i) {
        Vec3 p1 = vertices[edges[i][0]];
        Vec3 p2 = vertices[edges[i][1]];

        // Project 3D points to 2D screen space
        ImVec2 p1_2d = Project3DTo2D(p1);
        ImVec2 p2_2d = Project3DTo2D(p2);

        // Draw line
        background->AddLine(p1_2d, p2_2d, ImGui::GetColorU32(color));
    }
}

ImVec4 HealthToColor(int health)
{
    ImVec4 color;
    if (health > 50)
    {
        color.x = (100 - health) * 5.1;
        color.y = 255;
    }
    if (health < 50)
    {
        color.x = 255;
        color.y = (health) * 5.1;
    }
    if (health == 50)
    {
        color.x = 255;
        color.y = 255;
    }
    color.z = 0;
    color.w = 255;

    return color;
}

/*
void DrawOutlinedBox(ImVec4 rect, ImVec4 color, int thickness)
{
    DrawBox(ImVec4(rect.x + 1, rect.y + 1, rect.z - 1, rect.w - 1), ImVec4(0,0,0,color.w), 1);
    DrawBox(ImVec4(rect), color, thickness);
    DrawBox(ImVec4(rect.x - 1, rect.y - 1, rect.z + 1, rect.w + 1), ImVec4(0,0,0,color.w), 1);
}*/

void DrawFilledRect(float x, float y, float width, float height, ImVec4 color, ImDrawList* background)
{
    if (background) {
        background->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), IM_COL32(color.x, color.y, color.z, color.w));
    }
}

void DrawOutlinedFilledRect(float x, float y, float width, float height, ImVec4 color, ImDrawList* background)
{
    DrawFilledRect(x, y, width, height, color, background);
    DrawBox2(x - 1, y - 1, width + 2, height + 2, ImVec4(0, 0, 0, color.w), 1, background);
}

/*
void DrawCircle(float X, float Y, float radius, bool filled, IM_COL32, int tesselation, float thickness) {
    ImDrawList* background = ImGui::GetBackgroundDrawList();
    if(background) {
        if(filled) {
            background->AddCircleFilled(ImVec2(X, Y), radius, ImColor(color.x,color.y,color.z,color.w), tesselation);
        } else {
            background->AddCircle(ImVec2(X, Y), radius, IM_COL32(color.x,color.y,color.z,color.w), tesselation, thickness);
        }
    }
}*/

#include <string>
void DrawTexts(ImVec2 position, ImVec4 color, std::string text, ImFont* font, ImDrawList* background) {
    if (background) {
        ImGuiContext& g = *GImGui;
        ImGui::PushFont(font);
        background->AddText(g.Font, g.FontSize, ImVec2(position.x - 2, position.y - 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x, position.y - 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x + 2, position.y - 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x + 2, position.y), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x + 2, position.y + 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x, position.y + 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x - 2, position.y + 2), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, ImVec2(position.x - 2, position.y), IM_COL32(0, 0, 0, color.w), text.c_str());
        background->AddText(g.Font, g.FontSize, position, ImColor(color.x, color.y, color.z, color.w), text.c_str());
        ImGui::PopFont();
    }
}

float BOG_TO_GRD(float BOG) {
    return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
    return (M_PI / 180) * GRD;
}


void DrawBox4(float x, float y, float width, float height, ImVec4 bgColor, ImVec4 edgeColor, int thickness, ImDrawList* background) {
    ImVec2 topLeft(x, y);
    ImVec2 topRight(x + width, y);
    ImVec2 bottomRight(x + width, y + height);
    ImVec2 bottomLeft(x, y + height);

    float cornerLength = fmin(width, height) * 0.2f;  // Dynamic length of the corner lines (10% of the smallest dimension)

    // Draw filled background
    background->AddRectFilled(topLeft, bottomRight, ImColor(bgColor), 0.0f);

    // Top-left corner
    DrawCorner(topLeft, ImVec2(topLeft.x + cornerLength, topLeft.y), edgeColor, thickness, background);
    DrawCorner(topLeft, ImVec2(topLeft.x, topLeft.y + cornerLength), edgeColor, thickness, background);

    // Top-right corner
    DrawCorner(topRight, ImVec2(topRight.x - cornerLength, topRight.y), edgeColor, thickness, background);
    DrawCorner(topRight, ImVec2(topRight.x, topRight.y + cornerLength), edgeColor, thickness, background);

    // Bottom-right corner
    DrawCorner(bottomRight, ImVec2(bottomRight.x - cornerLength, bottomRight.y), edgeColor, thickness, background);
    DrawCorner(bottomRight, ImVec2(bottomRight.x, bottomRight.y - cornerLength), edgeColor, thickness, background);

    // Bottom-left corner
    DrawCorner(bottomLeft, ImVec2(bottomLeft.x + cornerLength, bottomLeft.y), edgeColor, thickness, background);
    DrawCorner(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - cornerLength), edgeColor, thickness, background);
}

void DraEdgesRectFil(float x, float y, float width, float height, ImVec4 BGColor, ImVec4 color, ImDrawList* background) {
    // Separate background color (with transparency) and edge color
    ImVec4 bgColor = ImVec4(BGColor.x, BGColor.y, BGColor.z, BGColor.w * 0.3f);  // Transparent background
    ImVec4 edgeColor = ImVec4(color.x, color.y, color.z, 1.0f);  // Solid edges

    int thickness = fmax(2, (int)(fmin(width, height) * 0.02f));

    DrawBox4(x + 3 - 1, y + 3 - 1, width - 5 * 2 + 2, height - 3 * 2 + 2, bgColor, edgeColor, thickness, background);
}