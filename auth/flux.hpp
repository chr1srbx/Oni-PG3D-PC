#pragma once

namespace flux {
    bool set_application(const std::string& id);
    void authenticate(const std::string& license, const std::string& hwid = "");

    namespace field {
        template <typename T>
        T get(const std::string& field);
    }

    namespace variables {
        template <typename T>
        T get(const std::string& name);

        void download(const std::string& name, std::vector<char>& data);
    }
}
