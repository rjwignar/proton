#pragma once

#include <Processors/Transforms/Streaming/AggregatingTransformWithSubstream.h>

namespace DB
{
namespace Streaming
{
class WindowAggregatingTransformWithSubstream : public AggregatingTransformWithSubstream
{
public:
    WindowAggregatingTransformWithSubstream(Block header, AggregatingTransformParamsPtr params_, const String & log_name, ProcessorID pid_);

    ~WindowAggregatingTransformWithSubstream() override = default;

protected:
    void finalize(const SubstreamContextPtr & substream_ctx, const ChunkContextPtr & chunk_ctx) override;

private:
    inline void doFinalize(Int64 watermark, const SubstreamContextPtr & substream_ctx, const ChunkContextPtr & chunk_ctx);

    virtual WindowsWithBuckets getFinalizedWindowsWithBuckets(Int64 watermark, const SubstreamContextPtr & substream_ctx) const = 0;
    virtual void removeBucketsImpl(Int64 watermark, const SubstreamContextPtr & substream_ctx) = 0;
    virtual bool needReassignWindow() const = 0;
};

}
}
