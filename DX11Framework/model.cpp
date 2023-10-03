#include "model.h"

Model::Model(ID3D11Device* device) {
    _modelBuffer = new ModelBuffer(device);
    _vertexShader = NULL;
    _pixelShader = NULL;
}

Model::Model(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<WORD> indices) {
    _modelBuffer = new ModelBuffer(device, verts, indices);
    _vertexShader = NULL;
    _pixelShader = NULL;
}

Model::~Model() {
    delete _modelBuffer;
    _vertexShader = NULL;
    _pixelShader = NULL;
}

void Model::Render(ID3D11DeviceContext* context) {
    //Set object variables and draw
    UINT stride = { sizeof(SimpleVertex) };
    UINT offset = 0;
    ID3D11Buffer* vBuffer = _modelBuffer->GetVertBuffer()->GetBuffer();
    context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
    ID3D11Buffer* iBuffer = _modelBuffer->GetIndBuffer()->GetBuffer();
    context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R16_UINT, 0);

    context->VSSetShader(_vertexShader, nullptr, 0);
    context->PSSetShader(_pixelShader, nullptr, 0);

    context->DrawIndexed(GetIndices(), 0, 0);
}