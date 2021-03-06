namespace rapid
{
    class alignas(16) plane
    {
    public:
        XMVECTOR P;

        plane() noexcept {}
        plane(FXMVECTOR p) noexcept: P(p) {}
        plane(const float x, const float y, const float z, const float d) noexcept: P(XMVectorSet(x, y, z, d)) {}
        plane(const vector3& p, const vector3& n) noexcept: P(XMPlaneFromPointNormal(p.V, n.V)) {}
        plane(const vector3& p1, const vector3& p2, const vector3& p3) noexcept: P(XMPlaneFromPoints(p1.V, p2.V, p3.V)) {}

        plane operator*(const matrix& m) const noexcept { return XMPlaneTransform(P, m); }
        const plane& operator*=(const matrix& m) noexcept { P = XMPlaneTransform(P, m); return *this; }

        bool operator==(const plane& p) const noexcept { return XMPlaneEqual(P, p.P); }
        bool nearEqual(const plane& p, const vector& eps) const noexcept { return XMPlaneNearEqual(P, p.P, eps); }
        bool operator!=(const plane& p) const noexcept { return XMPlaneNotEqual(P, p.P); }

        bool nan() const noexcept { return XMPlaneIsNaN(P); }
        bool infinite() const noexcept { return XMPlaneIsInfinite(P); }

        vector dot(const vector4& v) noexcept { return XMPlaneDot(P, v.V); }
        vector dotNormal(const vector3& n) noexcept { return XMPlaneDotNormal(P, n.V); }
        vector distance(const vector3& p) noexcept { return XMPlaneDotCoord(P, p.V); }
        void normalizeEst() noexcept { P = XMPlaneNormalizeEst(P); }
        plane normalizedEst() const noexcept { return XMPlaneNormalizeEst(P); }
        void normalize() noexcept { P = XMPlaneNormalize(P); }
        plane normalized() const noexcept { return XMPlaneNormalize(P); }

        vector intersectLine(const vector3& p1, const vector3& p2) noexcept { return XMPlaneIntersectLine(P, p1.V, p2.V); }
        void intersectPlane(const plane& p, vector3 *p1, vector3 *p2) noexcept { XMPlaneIntersectPlane(&p1->V, &p2->V, P, p.P); }

        void store(float4 *v) const noexcept { XMStoreFloat4(v, P); };
        void store(float4a *v) const noexcept { XMStoreFloat4A(v, P); };
    };
} // namespace rapid
