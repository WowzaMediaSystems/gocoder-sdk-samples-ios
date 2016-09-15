sdk_binary_path="${PROJECT_DIR}/WowzaGoCoderSDK.framework/WowzaGoCoderSDK"

if [ ! -f "${sdk_binary_path}" ]
then
echo "error: ⚠️⚠️⚠️The WowzaGoCoderSDK binary cannot be found. This may be because you are building from the sample app code on GitHub which does not include the SDK binary. Please visit https://www.wowza.com/products/gocoder/sdk to inquire about licensing the SDK.⚠️⚠️⚠️"
exit 1
fi