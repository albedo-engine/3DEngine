#pragma once

#include "../../../utils/headers/common.hpp"
#include <scene/node.hpp>
#include <components/component.hpp>

namespace Engine
{
  namespace Components
  {
    /** \class Transform
     *
     *  \brief An abstract way of describing 3D transformations.
     */
    class Transform : public Component
    {
      public:
        /** \enum Direction
         *
         *  \brief An abstract way of describing orientation-relative directions.
         */
        enum Direction {
          /** The forward transform direction. (0, 0, -1) by default. */
          FORWARD,
          /** The backward transform direction. (0, 0, 1) by default. */
          BACKWARD,
          /** The westward transform direction. (-1, 0, 0) by default. */
          WESTWARD,
          /** The eastward transform direction. (1, 0, 0) by default. */
          EASTWARD,
          /** The upward transform direction. (0, 1, 0) by default. */
          UPWARD,
          /** The downard transform direction. (0, -1, 0) by default. */
          DOWNWARD
        };

      public:
        typedef std::shared_ptr<Transform>    TransformPtr;

      public:
        TransformPtr
        static inline
        create()
        {
          return std::make_shared<Transform>();
        }

      public:
        Transform();

      public:
        bool
        unique() override;

      public:
        /** \brief Moves the transform by a given vector in its local coordinates system,
         * relative to the current position.
         *
         * \param translation_vector
         * the vector translating the transform.
         */
        void
        translate(const glm::vec3& translation_vector);


        /** \brief Moves the transform by a given amount in its local coordinates system,
         * relative to a direction obtained from the transform orientation.
         *
         * \param amount
         * a scalar by which the direction will be multiplied.
         * \param relative_direction
         * the given direction that will be replaced by its equivalent normalized vector.
         */
        void
        translate(float amount, Direction relative_direction);


        /** \brief Moves the transform to a given point in its local coordinates system,
         * relative to the world origin (0, 0, 0).
         *
         * \param position
         * the new position at which the transform should be located.
         */
        void
        translateTo(const glm::vec3& position);


        /** \brief Rotates the transform by a given amount,
         * relative to its local origin, the transform center of mass.
         *
         * \param angleDegrees
         * a floating point value representing the rotation amount, in degrees.
         * \param axis
         * a 3D vector representing the rotation-axis, arround which the Transform will be rotated.
         */
        void
        rotate(float angleDegrees, const glm::vec3& axis);


        /** \brief Rotates the transform by a given amount,
          * relative to its local origin, the transform center of mass.
          *
          * \param quaternion
          * the quaternion representing the rotation to apply on the Transform.
          */
        void
        rotate(const glm::quat& quaternion);


        /** \brief Rotates the transform from the
          * initial rotation (the identity quaternion) to the given value,
          * and relative to its local origin, the transform center of mass.
          *
          * \param quaternion
          * the quaternion representing the rotation to apply on the Transform.
          */
        void
        rotateTo(const glm::quat& quaternion);


        /** \brief Scales the transform by the given vector,
         * relative to its local coordinates system.
         *
         * \param scale
         * the vector composed by the scale amount on 3 axis.
         */
        void
        scale(const glm::vec3& scale);


        /** \brief Scales the transform to the given vector,
         * relative to its local coordinates system.
         *
         * \param scale
         * the vector composed by the scale amount on 3 axis.
         */
        void
        scaleTo(const glm::vec3& scale);


        /** \brief Makes the Transform look at a given 3D point.
         *
         * \param targetPoint
         * the 3D target point represented as a vector, expressed in the world coordinates system.
         */
        void lookAt(const glm::vec3& targetPoint);


        /** \brief Makes the Transform look at a given Transform.
         *
         * \param transformTarget
         * the target Transform.
         */
        void lookAt(const TransformPtr& transformTarget);

      public:
        glm::vec3 getLocalPos() const;
        glm::vec3 getWorldPos();

        glm::vec3 getDirection() const;
        glm::vec3 getUp() const;
        glm::vec3 getRight() const;

        const glm::quat& getRotationQuat();

        const glm::mat4& getWorldMatrix();

      private:
        glm::vec3 localPos_;
        glm::vec3 localScale_;
        glm::quat quaternion_;

        glm::mat4 worldMatrix_;

    };
  } // namespace Component
} // namespace Engine
